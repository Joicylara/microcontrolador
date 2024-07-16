var DDRAM = new Array(104);
var CGRAM = new Array(64);

var lastAdrsSet='DDRAM';
var AC = 0;
var AC = 0;
var range = 16; // 16 chars only

//function set
var DL = 1;  //  8-bit interface data
var N = 0;   //  1-line display
var F = 0;   //  5 * 8 dot character font
//Display on/off control:
var D = 0;   //  Display off
var C = 0;   //  Cursor off
var B = 0;   //  Blinking off
//Entry mode set:
var ID = 1;  //  Increment by 1
var S = 0;   //  No shift
// Cursor or display shift command:
var RL = 1;
var SC = 0;

function reset(){
	DDRAM = new Array(104);
	CGRAM = new Array(64);

	lastAdrsSet='DDRAM';
	AC = 0;
	range = 16; // 16 chars only
	
	//function set
	DL = 1;  //  8-bit interface data
	N = 0;   //  1-line display
	F = 0;   //  5 * 8 dot character font
	//Display on/off control:
	D = 0;   //  Display off
	C = 0;   //  Cursor off
	B = 0;   //  Blinking off
	//Entry mode set:
	ID = 1;  //  Increment by 1
	S = 0;   //  No shift
	range = 16; // 16 chars only
	document.ctrl.lcdpinsHex.value = 0;
	document.ctrl.lcdpinsDec.value = 0;
	document.ctrl.ctrlpins.value = '  Disabled, write to IR';
	

	for(var q=0;q<DDRAM.length;q++){
			DDRAM[q]=20;
	}

	for(var q=0;q<CGRAM.length;q++){
			CGRAM[q]=0;
	}
	
	for(var i=0; i < 8; i++){
		for(var j=0; j < 8; j++){
			chrtbl[i][j]=0;
		
		}
	}
	
	shiftChars = 0;
	
	initCurrDispChrs();
	
	updateDisp();
	
	ln2Off();
	
	blinkCur();
	updateStats();
	
	
	
	
	
	// alert('reset done !')
}


var upNib = 0;
var lowNib = 0;
var gotUpNib = 0
function lcd(data,eGoLow,rwState,rsState){
	//window.status=('data: '+data+'\n'+'eGoLow: '+eGoLow+'\n'+'rwState: '+rwState+'\n'+'rsState: '+rsState)
	
	if(eGoLow == 1){ // E goes LOW, this is when instructions are evaluated, chars written 
		if(rsState == 0 & rwState == 0){
			//alert('write to IR, \n evaluate instruction')
			if(DL == 1){
				evalInstr(data);
			}
			else{
				if(gotUpNib == 0){
					upNib = data;
					gotUpNib = 1;
					instrpeek(instr);
				}
				else{
					lowNib = data;
					gotUpNib = 0;
					evalInstr((upNib << 4) | lowNib);
				}
				
			}
		}
		if(rsState == 1 & rwState == 0){
			//alert('write to DR, \n print character')
			if(DL == 1){
				writeData(data);
			}
			else{
				if(gotUpNib == 0){
					upNib = data;
					gotUpNib = 1;
					instrpeek(instr)
				}
				else{
					lowNib = data;
					gotUpNib = 0;
					writeData((upNib << 4) | lowNib);
				}
				
			}
			
		instrpeek(baseConv(document.ctrl.lcdpinsHex.value,16));
		}
		updateStats();
		return;
	}
	
	if(eGoLow != 1 & rwState == 1){ // E is 1. Data or address reads are done 
		if(rsState == 0 & rwState == 1){
			alert('Read BF & address, \n Reads are not implemented! \n         Yet !');
		}
		if(rsState == 1 & rwState == 1){
			alert('Read Data Register, \n Reads are not implemented! \n         Yet !');
		}
		return;
	}
}

function evalInstr(instr){
	clearMsgs();
	addMsg('On E going LOW, executed instruction was:');
	
	if((instr & maskSetDDRAMadrs) == instrSetDDRAMadrs){
		setDDRadrs(instr & 0x7f);
		lastAdrsSet = 'DDRAM';
		addMsg('\n Set DDRAM address to ' +AC);
		return;
	}
	
	if((instr & maskSetCGRAMadrs) == instrSetCGRAMadrs){
		AC = (instr & 0x3f)+64;
		updateUndCurs()
		lastAdrsSet = 'CGRAM';
		addMsg('\n Set CGRAM address to ' + (AC - 64));
		return;
	}
	
	if((instr & maskFuncSet) == instrFuncSet){
		addMsg('\n Function set commmmmand : ');
		if(instr & eithtBitMode){
			addMsg('8 bit mode ON, ');
			if(DL == 0){
				DL = 1;
				for(var i=0; i<4; i++){
					togImage('d'+i);
				}
			}
			DL = 1;
		}
		else{
			addMsg('4 bit mode ON, ');
			/*
			//fix... 15 August 2004 14:09
			if((gotUpNib == 0) && (DL==1)){
				upNib = instr >> 4;
				gotUpNib = 1;
				instr = instr >> 4
			}
			// end of fix ...15 August 2004 14:09
			*/
			DL = 0;
			for(var i=0; i<4; i++){
				document['d'+i].src = 'b1t.gif';
			}
			var newVal = document.ctrl.lcdpinsDec.value >> 4;
			document.ctrl.lcdpinsHex.value = baseDisp(newVal,16);
			document.ctrl.lcdpinsDec.value = baseDisp(newVal,10);
		}
		
		if(instr & twoLines){
			addMsg('2 lines, ');
			N = 1;
			range = 32;
			ln2On();
			updateDisp();
		}
		else{
			addMsg('1 line, ');
			N = 0;
			range = 16;
			updateDisp();
			ln2Off();
			
		}
		
		if(instr & largeFont){
			addMsg('5*10 font, ');
			F = 1;
			alert('\nThis LCD supports only 5*7 fonts !!!');
		}
		else{
			addMsg('5*8 font, ');
			F = 0;
		}
		
		return;
	}
	
	if((instr & maskCursorDisplay) == instrCursorDisplay){
		addMsg('\n Cursor or display shift command:');	
		if(instr & rightLeft){
			addMsg('right, ');
			RL = 1;
		}
		else{
			addMsg('left, ');
			RL = -1;
		}
		if(instr & shiftOrCursorMove){
			addMsg('shift display ');
			SC = 1;
			shiftChars -=RL;
			lastAdrsSet = 'DDRAM';
			updateDisp();
		}
		else{
			addMsg('move cursor ');
			SC = 0;
			lastAdrsSet = 'DDRAM';
			incdcrDDRadrs(RL);
			updateDisp();
		}

		return;
	}
	
	if((instr & maskEntryMode) == instrEntryMode){
		addMsg('\n Entry mode set: ');
		if(instr & incCursorPos){
			addMsg('increase cursor position, ');
			ID = 1;
		}
		else{
			addMsg('decrease cursor position, ');
			ID = -1; 
		}
		
		if(instr & scrollDisp){
			addMsg('scroll display ON, ');
			S = 1;
		}
		else{
			addMsg('scroll display OFF, ');
			S = 0;
		}
		
		return;
	}
	
	if((instr & maskDisplayCtrl) == instrDisplayCtrl){
		addMsg('\n Display ON/OFF control: ');
		if(instr & displayOn){
			addMsg('display ON, ');
			D = 1;
			dispBlanked = 0;
			updateDisp();
		}
		else{
			addMsg('display OFF, ');
			D  = 0;
			updateDisp();
		}
		
		if(instr & cursorOn){
			addMsg('cursor ON, ');
			C = 1;
			updateUndCurs();
		}
		else{
			addMsg('cursor OFF, ');
			C  = 0;
			updateUndCurs();
		}
		
		if(instr & blinkOn){
			addMsg('blink ON, ');
			B = 1;
		}
		else{
			addMsg('blink OFF, ');
			B  = 0;
		}	
		
		return;
	}
	
	
	if((instr & maskClearDisplay) == instrClearDisplay){
		addMsg('\n Clear display.');
		for(var i=0; i<104;i++){
			DDRAM[i]=0x20;
		}
		ID = 1;
		setDDRadrs(0);
		lastAdrsSet = 'DDRAM';
		updateDisp();
		
		return;
	}

	if((instr & maskCursorHome) == instrCursorHome){
		addMsg('\n Cursor home. ');
		shiftChars = 0;
		setDDRadrs(0);
		lastAdrsSet = 'DDRAM';
		updateDisp();
		
		return;
	}
	
	addMsg('\nInvalid instruction !');
	return;
}

function writeData(data){
	if(lastAdrsSet == 'DDRAM'){
		DDRAM[AC] = data;
		if(S){
			shiftChars += ID;
		}
		incdcrDDRadrs(ID);
		updateDisp();
	}
	else{
		//alert('writing to cgram viewer')
		CGRAM[AC%64] = data;
		var ACmn64 = AC % 64;
		chrtbl[Math.floor(ACmn64/8)][ACmn64 % 8] = data & 31; //this goes to CGRAM viewer
		document['cgp'+ ACmn64].src = (data & 31) +'.gif';
		incdcrCGRadrs(ID); 
		cgramChanged();
	}

}

function readBfAndAdr(){

}

function readDataReg(){


}

var adrs = 1; 
var chr = 0;
currDispChrs = new Array(32);
var shiftChars = 0;
//var offset = 0
function updateDisp(){
	setCurrDispChrs();
	//updateUndCurs();
	if(D==0){
		if(dispBlanked != 1){
			blankDisp();
			
		}
		return;
	}
	
	if(N == 0){
		if(shiftChars > 79 || shiftChars < -79){
			shiftChars=0
		}
	}
	else{
		if(shiftChars > 39 || shiftChars < -39){
			shiftChars=0
		}
	}
	
	if(N == 0){
		for(var ln=0; ln<16; ln++){
			if(currDispChrs[ln][chr] != DDRAM[currDispChrs[ln][adrs]]){
				pchr(DDRAM[currDispChrs[ln][adrs]],ln)
				currDispChrs[ln][chr] = DDRAM[currDispChrs[ln][adrs]]
				//cursPos = DDRAM[currDispChrs[ln][adrs]]
				//blinkChar = DDRAM[currDispChrs[ln][adrs] + 1]
			}
		}	
	}	
	else{
		for(var ln=0; ln<32; ln++){
			if(currDispChrs[ln][chr] != DDRAM[currDispChrs[ln][adrs]]){
				pchr(DDRAM[currDispChrs[ln][adrs]],ln)
				currDispChrs[ln][chr] = DDRAM[currDispChrs[ln][adrs]]
				//cursPos = DDRAM[currDispChrs[ln][adrs]]
				//blinkChar = DDRAM[currDispChrs[ln][adrs] + 1]
			}
		}	
	}
	/* thhese are to clear the cursor trace in case of LCD scroll*/
	pchr(currDispChrs[0][chr],0)
	pchr(currDispChrs[15][chr],15)
	if(range == 32){
		pchr(currDispChrs[16][chr],16)
		pchr(currDispChrs[31][chr],31)
	}
	updateUndCurs();
}

function cgramChanged(){
	if(D == 1){
		for(var i=0; i<range; i++){
			if(currDispChrs[i][chr] < 8){
				pchr(currDispChrs[i][chr],i)
			}
		}
		
		updateUndCurs()
	}
}


var prevDDRAMadrCursAt = 0;
var cursPos = 0;
var cursOutOfDisp = 0
var undCursClrd = 0
function updateUndCurs(){
	cursOutOfDisp = 1
	if(D == 1){
		for(var i=0; i<range; i++){
			if(currDispChrs[i][adrs] == prevDDRAMadrCursAt){
				pchr(DDRAM[currDispChrs[cursPos][adrs]],cursPos)
			}	
		}
	}
	else if(D == 0 || ( C == 0 && B == 0)){
		document['p'+ parseInt(cursPos * 8 + 7)].src = '0.gif';
		//currDispChrs[cursPos][chr] = 333;	// this is a fake value... so that the characer gets refreshed when cursor goes somewhere else
		//alert('remove und curs at ln 426')
		return;
	}
		
	for(var i=0; i<range; i++){
		if(currDispChrs[i][adrs] == AC){
			prevDDRAMadrCursAt = AC;
			cursPos = i;
			blinkChar = currDispChrs[i][chr];
			cursOutOfDisp = 0;
		}
	}
	
	if(C == 1 && cursOutOfDisp == 0){
		document['p'+ parseInt(cursPos * 8 + 7)].src = '31.gif';
		//currDispChrs[cursPos][chr] = 333;	// this is a fake value... so that the characer gets refreshed when cursor goes somewhere else

		undCursClrd = 0
		//alert('put und curs')
	}
	
	/*if(C == 1 && cursOutOfDisp == 1 && undCursClrd == 0){
			pchr(blinkChar,cursPos)
			undCursClrd = 1
			//alert(' cleared und curs at >>>>' + cursPos)
	}*/
	
}



var blinked = 0;
var blinkChar = 0x20;
var undCntr = 0;
function blinkCur(){
	
	if(B == 0 || D == 0 || cursOutOfDisp == 1){
		if(blinked == 1 && cursPos < range && cursOutOfDisp == 0){
			pchr(blinkChar,cursPos)
			//currDispChrs[cursPos][chr] = 333;
			blinked = 0
			if(C == 1 && cursOutOfDisp == 0){
				document['p'+ parseInt(cursPos * 8 + 7)].src = '31.gif'
				//alert('put und curs at ln 464')
				//undCntr++
				//window.status = undCntr;
			}
		}
		setTimeout("blinkCur()",379);
		return;
	}
	if(blinked == 1){
		pchr(blinkChar,cursPos)
		//currDispChrs[cursPos][chr] = 333;
		blinked = 0
		setTimeout("blinkCur()",379)
		if(C == 1 && cursOutOfDisp == 0){
				document['p'+ parseInt(cursPos * 8 + 7)].src = '31.gif'
				//currDispChrs[cursPos][chr] = 333;
				//alert('put und curs at ln 478')
		}
	}
	else {
		pchr(255,cursPos)
		document['p'+ parseInt(cursPos * 8 + 7)].src = '31.gif'
		//currDispChrs[cursPos][chr] = 333;
		blinked = 1
		setTimeout("blinkCur()",379)
		/*if(C == 1 && cursOutOfDisp == 0){
				document['p'+ parseInt(cursPos * 8 + 7)].src = '31.gif'
		}*/
	}
}

var dispBlanked = 0;
function blankDisp(){
	for(var i=0;i< range * 8;i++){
		document['p'+i].src='0.gif';
	}
	for(var ln=0; ln<32; ln++){
		currDispChrs[ln][chr] = 0x20
	}
	
	dispBlanked = 1
}

function setDDRadrs(address){
	AC = address
	if(N==0){
		if(AC > 79){
			 AC = 0
		}
	}
	else{
		if(AC > 64){
		}
		if(AC > 39 && AC < 64){
			AC = 64
		}
		if(AC > 103){
			AC = 0
		}
	}
	updateUndCurs()
}

function incdcrDDRadrs(incordcr){
	//alert('ddradrs decreasing !' + AC)
	if(N == 0){
		AC += incordcr
		if(AC < 0){AC = 79}
		AC %= 80
	}
	else{
		AC += incordcr
		if(AC < 0){
			AC = 103
		}
		if(AC > 39 && AC < 64){
			AC = 64
		}
		if(AC > 103){
			AC = 0
		}
	}
	//if(AC < 0 || (AC > 39 && AC < 64) || AC >= 104){alert('AC invalid !!!! >>>>'+ AC)}
}

function incdcrCGRadrs(incordcr){
	AC += incordcr
	if(AC-64 < 0) {AC = 63}
	if(AC-64 > 63){AC = 0}
}

function initCurrDispChrs(){
	//if(N == 0){
		for(var i=0;i<16;i++){
			currDispChrs[i]= new Array(2)
			currDispChrs[i][chr]= 0x20;
			currDispChrs[i][adrs]= i;
		}
	//}
	//else{
		for(var i=16;i<32;i++){
			currDispChrs[i]= new Array(2)
			currDispChrs[i][chr]= 0x20;
			currDispChrs[i][adrs]= 48 + i;
		}
	//}

}

function setCurrDispChrs(){
	if(N == 0){
		for(var i=0; i<16; i++){ 
			//if(shiftChars < 0){
				currDispChrs[i][adrs]= (i + 80 + shiftChars) % 80	//adrs
			//}
		}
	}
	else{
		for(var i=0; i<16; i++){ 
			//if(shiftChars < 0){
				currDispChrs[i][adrs]= (i + 40 + shiftChars) % 40	//adrs
			//}
		}
		for(var i=16; i<32; i++){ 
			if(shiftChars < 0){
				currDispChrs[i][adrs]= (i + 40 + shiftChars + 48) //adrs
				if(currDispChrs[i][adrs] > 103)
					currDispChrs[i][adrs] = (currDispChrs[i][adrs] % 104) + 64
			}else{
				currDispChrs[i][adrs]= i  + shiftChars + 48	//adrs
				if(currDispChrs[i][adrs] > 103)
					currDispChrs[i][adrs] = (currDispChrs[i][adrs] % 104) + 64
			}
		}
	}
}

function updateStats(){
	cursOutOfDisp = 1;
	for(var i=0; i<range; i++){
		if(currDispChrs[i][adrs] == AC){
			cursOutOfDisp = 0;
		}
	}

	document.ctrl.lastAdrsSet.value = lastAdrsSet + '.';
	if(D == 1)
		document.ctrl.D.value = 'ON.';
	else
		document.ctrl.D.value = 'OFF.';	
		
	if(cursOutOfDisp == 1)
		document.ctrl.cursOutOfDisp.value = 'is invisible.';  
	else
		document.ctrl.cursOutOfDisp.value = 'is visible.';  

	if(ID == 1)
		document.ctrl.ID.value = 'increasing.';
	else
		document.ctrl.ID.value = 'decreasing.';
	
	if(S == 1)
		document.ctrl.S.value = 'ON.';
	else
		document.ctrl.S.value = 'OFF.';
	if(lastAdrsSet == 'CGRAM')	
		document.ctrl.AC.value = (AC-64);
	else
		document.ctrl.AC.value = AC;

	if(C == 0 && B == 0){
		document.ctrl.C.value = 'OFF.';
	}
	else{
		if(C == 1 && B == 1){
			document.ctrl.C.value = 'ON, blinking.';
		}
		if(C == 0 && B == 1){
			document.ctrl.C.value = 'blinking.';
		}
		if(C == 1 && B == 0){
			document.ctrl.C.value = 'ON.';
		}
	}
	
		
	if(N == 1){
		document.ctrl.ln2adr.value = currDispChrs[16][adrs] + '..' + currDispChrs[31][adrs];
	}
	else{
		document.ctrl.ln2adr.value =  '- -' ;
	}
		document.ctrl.ln1adr.value = currDispChrs[0][adrs] + '..' + currDispChrs[15][adrs];
}
