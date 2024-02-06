// preload all imgs
pix0  = new Image();
pix1  = new Image();
pix2  = new Image();
pix3  = new Image();
pix4  = new Image();
pix5  = new Image();
pix6  = new Image();
pix7  = new Image();
pix8  = new Image();
pix9  = new Image();
pix10 = new Image();
pix11 = new Image();
pix12 = new Image();
pix13 = new Image();
pix14 = new Image();
pix15 = new Image();
pix16 = new Image();
pix17 = new Image();
pix18 = new Image();
pix19 = new Image();
pix20 = new Image();
pix21 = new Image();
pix22 = new Image();
pix23 = new Image();
pix24 = new Image();
pix25 = new Image();
pix26 = new Image();
pix27 = new Image();
pix28 = new Image();
pix29 = new Image();
pix30 = new Image();
pix31 = new Image();
pixBlank = new Image();

b1 = new Image();
b2 = new Image();
b3 = new Image();
b4 = new Image();
b5 = new Image();
b6 = new Image();
b7 = new Image();
b8 = new Image();
b9 = new Image();
b1.src = "b0d.gif";
b2.src = "b1u.gif";
b3.src = "b0gd.gif";
b4.src = "b0gu.gif";
b5.src = "b0u.gif";
b6.src = "b1d.gif";
b7.src = "b1gd.gif";
b8.src = "b1gu.gif";
b9.src = "b1t.gif"		   

pix0.src  = "0.gif";
pix1.src  = "1.gif";
pix2.src  = "2.gif";
pix3.src  = "3.gif";
pix4.src  = "4.gif";
pix5.src  = "5.gif";
pix6.src  = "6.gif";
pix7.src  = "7.gif";
pix8.src  = "8.gif";
pix9.src  = "9.gif";
pix10.src = "10.gif";
pix11.src = "11.gif";
pix12.src = "12.gif";
pix13.src = "13.gif";
pix14.src = "14.gif";
pix15.src = "15.gif";
pix16.src = "16.gif";
pix17.src = "17.gif";
pix18.src = "18.gif";
pix19.src = "19.gif";
pix20.src = "20.gif";
pix21.src = "21.gif";
pix22.src = "22.gif";
pix23.src = "23.gif";
pix24.src = "24.gif";
pix25.src = "25.gif";
pix26.src = "26.gif";
pix27.src = "27.gif";
pix28.src = "28.gif";
pix29.src = "29.gif";
pix30.src = "30.gif";
pix31.src = "31.gif";
pixBlank.src = "blnk.gif";

function evaluator() {
  	eval(document.ctrl.scriptBox.value);

}


function pchr(chrnum, pos){
	var pos = pchr.arguments[1] * 8 
	for(var i=0;i<7;i+=1){
		document['p'+ (pos+i)].src = chrtbl[chrnum][i]+'.gif'
	}
	
	if(chrnum < 8){
		document['p'+ (pos+7)].src = chrtbl[chrnum][7]+'.gif'
	}else{
		document['p'+ (pos+7)].src = '0.gif'
	}
}


function ln2Off(){
	for(var i=128; i < 256; i++){
		document['p'+ i].src = 'blnk.gif'
	}
}
function ln2On(){
	for(var i=128; i < 256; i++){
		document['p'+ i].src = '0.gif'
	}
}


function togImage(imgName) {
	if(DL == 0 && parseInt(imgName.charAt(1),10) < 4){
		alert('LCD is in 4-bit mode now. Only the upper nibble of the data bus is available.')
		return
	}
	var newVal=0
	var pixState = document[imgName].src.charAt((document[imgName].src.length) - 6)
	//alert(document[imgName].src.charAt((document[imgName].src.length) - 6))
	if (pixState == "0") { 
		document[imgName].src = 'b1u.gif'
	}
	else{ 
		document[imgName].src = 'b0u.gif'
	}
	if(DL == 1){
		for(var i=0; i<8; i++){
			pixState = document['d'+i].src.charAt((document['d'+i].src.length) - 6)
			if(pixState == 1){
				newVal += Math.pow(2,i)
			}
		} 
	}
	else{
		for(var i=4; i<8; i++){
			pixState = document['d'+i].src.charAt((document['d'+i].src.length) - 6)
			if(pixState == 1){
				newVal += Math.pow(2,(i-4))
			}
		}
	}
	//alert(newVal)
	document.cgpixels.src = (newVal & 31) + '.gif'
	showPchr(newVal)
	document.ctrl.lcdpinsHex.value = newVal.toString(16).toUpperCase()
	document.ctrl.lcdpinsDec.value = newVal.toString(10).toUpperCase()
	document.ctrl.lcdpinsChar.value = ascii.charAt(newVal);
	instrpeek(newVal)
}

function inpChanged(box){
	var tmpVal = 0;
	
	if(box == 'hex'){
		tmpVal = parseInt(document.ctrl.lcdpinsHex.value,16);
        if(isNaN(tmpVal)) {
            return;
        }
		document.ctrl.lcdpinsDec.value = tmpVal.toString()
        document.ctrl.lcdpinsChar.value = ascii.charAt(parseInt(document.ctrl.lcdpinsHex.value), 16);
	}
	if(box == 'dec'){		
        tmpVal = parseInt(document.ctrl.lcdpinsDec.value,10);	
        if(isNaN(tmpVal)) {
            return;
        }
		document.ctrl.lcdpinsHex.value = tmpVal.toString(16).toUpperCase()
        document.ctrl.lcdpinsChar.value = ascii.charAt(parseInt(document.ctrl.lcdpinsDec.value), 10);
	} 
	if(box == 'chr'){
        tmpVal = document.ctrl.lcdpinsChar.value.charCodeAt(0)	
        if(isNaN(tmpVal)) {
            return;
        }
		document.ctrl.lcdpinsHex.value = tmpVal.toString(16).toUpperCase()
		document.ctrl.lcdpinsDec.value = tmpVal.toString()
    }
	
	if((tmpVal > 0xff && DL == 1) || (tmpVal > 0xf && DL == 0 )){
		alert('input too big !')
		tmpVal = 0 //reset tmpVal
		document.ctrl.lcdpinsHex.value = tmpVal
		document.ctrl.lcdpinsDec.value = tmpVal
	}
	
	document.cgpixels.src = (tmpVal & 31) + '.gif'
	showPchr(tmpVal)
	var binValStr = tmpVal.toString(2)
	var DataLen = 8
	if(DL == 1){
		for(var i=7;i >= 0;i--){
			if(i > binValStr.length-1){
				document['d'+i].src = 'b0u.gif';
			}
			else{
				document['d'+i].src = 'b'+ binValStr.charAt(binValStr.length -1 -i) +'u.gif';
			}
		}
	}
	else{
		binValStr = baseDisp((tmpVal << 4),2);
	for(var i=7;i >= 4;i--){
			if(i > binValStr.length-1){
				document['d'+i].src = 'b0u.gif';
			}
			else{
				document['d'+i].src = 'b'+ binValStr.charAt(binValStr.length -1 -i) +'u.gif';
			}
		}
	}
	
	instrpeek(tmpVal)
}


var rwState = 0
var rsState = 0
var eState  = 0


function togImageC(imgName) {
	var pixState = document[imgName].src.charAt((document[imgName].src.length) - 7)
	if (pixState == "0") { 
		document[imgName].src = 'b1gd.gif'
	}
	else { 
		document[imgName].src = 'b0gd.gif'
	}
	rwState = document.rw.src.charAt((document[imgName].src.length) - 7)
	rsState = document.rs.src.charAt((document[imgName].src.length) - 7)
	eState  = document.e.src.charAt((document[imgName].src.length) - 7)
	var statusMsg = ''
	if(rsState == 1 & rwState == 1)
		statusMsg = 'read DR'
	else if (rsState == 1 & rwState == 0)
		statusMsg = 'write to DR'
	else if (rsState == 0 & rwState == 0)
		statusMsg = 'write to IR'
	else if (rsState == 0 & rwState == 1)
		statusMsg = 'read BF and AC'
		
	instrpeek(baseConv(document.ctrl.lcdpinsHex.value,16))
	
	if (eState == 1){
		statusMsg = 'Enabled, ' + statusMsg
		lcd(parseInt(document.ctrl.lcdpinsHex.value,16), 0, rwState, rsState)
	}
	else{
		statusMsg = 'Disabled, ' + statusMsg
		if(imgName == 'e'){
			lcd(parseInt(document.ctrl.lcdpinsHex.value,16), 1,rwState, rsState)
		}
	}
		
	document.ctrl.ctrlpins.value = statusMsg
	//alert(rwState+' '+rsState+' '+eState)
}


function baseDisp(v,bn) // value, base. returns tring s representing value in given base
{
	var digitString = "0123456789ABCDEF";
	var s = ""; // string to return
	s = digitString.charAt(v % bn) + s; //this is DO and below is WHILE
	v = Math.floor(v/bn);				//JavaScript1.1 does not have DO WHILE loops !!!!!!!!!
	while(v)
	{
		s = digitString.charAt(v % bn) + s;
		v = Math.floor(v/bn);
	}

	return s;
}

function baseConv(s,b) // string, base
{
	var digitString = "0123456789abcdef";
	var v = 0; // value to return
	s = s.toLowerCase();
	for(var i = 0; i < s.length; i++) {
		v = v * b;
		var c = s.charAt(i);
		var d = digitString.indexOf(c);
		if((d != -1) && (d < b)) {
			v += d;
		}
		else {

			v = 'error'; //string is not of the correct base
			break;
		}
	}
	return v; //return the value of the string in base 10
}


function addMsg(str)
{
  document.ctrl.outpMsgs.value += str;
}

function clearMsgs(){
	document.ctrl.outpMsgs.value = ''
}

function  statBar(str){
	window.status = str;
}

function showPchr(chrnum){
	for(var i=0;i<7;i+=1){
		document['cprv' + i].src = chrtbl[chrnum][i]+'.gif'
	}
}


function instrpeek(instr){
	//alert(rsState)
	if(rwState == 1){
		clearMsgs()
		return
	}
	
	clearMsgs()
	
	if(DL == 0){
		if(gotUpNib == 1){
			instr = (upNib << 4) | parseInt(document.ctrl.lcdpinsHex.value,16);
			addMsg('LCD is in 4-Bit mode.\n Upper nibble is: ' + upNib +',and the lower one is: ' + document.ctrl.lcdpinsHex.value +'.\n' )
		}
		else{
			addMsg('LCD is in 4-Bit mode.\n Cannot evaluate instruction without getting the upper nibble.' )
			return
		}
	
	}
	
	
	if(rsState == 1){
		addMsg('RS is 1, data is: ' +  baseConv(document.ctrl.lcdpinsHex.value,16))
		if(lastAdrsSet == 'DDRAM'){
			addMsg('\n Last address set was DDRAM address.')
			addMsg('\n So,if written, data will go to DDRAM address: '+ AC)
			
		}
		else{
			addMsg('\n Last address set was CGRAM address.')
			addMsg('\n So,if written, data will go to CGRAM address: '+ (AC-64))
		}
		return
	}
	
	addMsg('RS is 0, the instruction is: ')
	
	if((instr & maskSetDDRAMadrs) == instrSetDDRAMadrs){
		//alert('set ddr aress instr 11')
		addMsg('\n Set DDRAM address to ' + (instr & 0x7f))
		//alert('set ddr aress instr 22')
		return
	}
	
	if((instr & maskSetCGRAMadrs) == instrSetCGRAMadrs){
		
		addMsg('\n Set CGRAM address to ' + (instr & 0x3f))
		return
	}
	
	if((instr & maskFuncSet) == instrFuncSet){
		addMsg('\n Function set commmmmand : ')
		if(instr & eithtBitMode){
			addMsg('8 bit mode ON, ')
	
		}
		else{
			addMsg('4 bit mode ON, ')
		}

		if(instr & twoLines){
			addMsg('2 lines, ')
		}
		else{
			addMsg('1 line, ')
		}
		
		if(instr & largeFont){
			addMsg('5*10 font, ')
			addMsg('\nThis LCD supports only 5*7 fonts !!!')
			addMsg('\nDo not use this command !')	
		}
		else{
			addMsg('5*8 font, ')
		}
		
		return
	}
	
	if((instr & maskCursorDisplay) == instrCursorDisplay){
		addMsg('\n Cursor or display shift command:')	
		if(instr & rightLeft){
			addMsg('right, ')
		}
		else{
			addMsg('left, ')
		}
		if(instr & shiftOrCursorMove){
			addMsg('shift display ')
		}
		else{
			addMsg('move cursor ')
		}

		return
	}
	
	if((instr & maskEntryMode) == instrEntryMode){
		addMsg('\n Entry mode set: ')
		if(instr & incCursorPos){
			addMsg('increase cursor position, ')
		}
		else{
			addMsg('decrease cursor position, ')
		}
		
		if(instr & scrollDisp){
			addMsg('scroll display ON, ')
		}
		else{
			addMsg('scroll display OFF, ')
		}
		return
	}
	
	if((instr & maskDisplayCtrl) == instrDisplayCtrl){
		addMsg('\n Display ON/OFF control: ')
		if(instr & displayOn){
			addMsg('display ON, ')
		}
		else{
			addMsg('display OFF, ')
		}
		
		if(instr & cursorOn){
			addMsg('cursor ON, ')
		}
		else{
			addMsg('cursor OFF, ')
		}
		
		if(instr & blinkOn){
			addMsg('blink ON, ')
		}
		else{
			addMsg('blink OFF, ')
		}	
		return
	}
	
	if((instr & maskClearDisplay) == instrClearDisplay){
		addMsg('\n Clear display.')
		return
	}

	if((instr & maskCursorHome) == instrCursorHome){
		addMsg('\n Cursor home. ')
		return
	}
	
	addMsg('\nThis is not a valid instruction !')
}


/******************* instructions *************************/
/**********************************************************/
	// LCD Command "Set Display Data RAM Address" = 10000000
	var instrSetDDRAMadrs  = 0x80;
	var maskSetDDRAMadrs = 0x80;

	//LCD Command "Set Display Character Generator RAM Address" = 01aaaaaa
	var instrSetCGRAMadrs  = 0x40;
	var maskSetCGRAMadrs = 0xc0;

	// LCD Command Function Set =  001dnfxx
	// d = 1 for 8-bit interface or 0 for 4-bit interface
	// n = for 2 line displays, n=1 allows both lines to be displayed
	// while n=0 only allows the first.
	// f = font size. f=1 is for 5x11 dots while f=0 is for 5x8 dots.
	var instrFuncSet   = 0x20;     // LCD Command "Function Set"
	var maskFuncSet  = 0xe0;     // 
	var eithtBitMode     = 0x10;    // d=1, if d=0 4 bit mode
	var twoLines       = 0x08;    // n=1, if d=0 8 bit mode 
	var largeFont    = 0x04;    // f=1 if f=0 large font

	// LCD Command "Cursor Display" = 0 0 0 1 SC RL x x
	// SC = 1 Sets cursor-move or display-shift
	// RL = 1 Shift right 0 = shift left
	var instrCursorDisplay   = 0x10;   // LCD Command "Cursor Display"
	var maskCursorDisplay  = 0xf0;   // 
	var shiftOrCursorMove = 0x8
	var rightLeft = 0x4
	
	//LCD Command "Entry Mode" = 000001is
	// i = 1 to increment or 0 to decrement the DDRAM address after each DDRAM access.
	// s = 1 to scroll the display in the direction specified by the i-bit when the
	//      cursor reaches the edge of the display window.
	var instrEntryMode  = 0x04;    // LCD Command "Entry Mode"
	var maskEntryMode = 0xfc;    // 
	var incCursorPos  = 0x02;    // i=1 if i=0 decrement
	var scrollDisp        = 0x01;    // s=1 if s=0 no scrolling

	// LCD Command Display Control = 00001dcb
	// d = 1 turn display on or 0 to turn display off
	// c = 1 turn cursor on or 0 to turn cursor off
	// b = 1 blinking cursor or 0 non-blinking cursor
	var instrDisplayCtrl   = 0x08;     // LCD Command "Display Control"
	var maskDisplayCtrl  = 0xf8;     // 
	var displayOn        = 0x04;    // d=1
	var cursorOn         = 0x02;    // c=1
	var blinkOn          = 0x01;    // b=1

	//LCD Command "Cursor Home" = 0000001x
	var instrCursorHome   = 0x02;   // LCD Command "Cursor Home"
	var maskCursorHome  = 0xfe;   // 

	// LCD Command Clear Display = 00000001
	var instrClearDisplay  = 0x01;
	var maskClearDisplay = 0xff;

/**********************************************************/
/****************** instructions end **********************/
