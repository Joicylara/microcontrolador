
function data(data){
	writeData(data);
}

function defCustChr(){
	instr(64);
	var customChars = Array();
	customChars[0] = Array(0,4,2,31,2,4,0,0 	    ); // right arrow				
	customChars[1] = Array(0,4,8,31,8,4,0,0 		); // left arrow	 			
	customChars[2] = Array(4,14,21,4,4,0,0,0 		); // up arrow	 				
	customChars[3] = Array(0,0,0,4,4,21,14,4		); // down arrow	 			
	customChars[4] = Array(8,20,20,8,5,6,5,5		); // single-character "OK"	 
	customChars[5] = Array(14,17,17,31,27,27,31,0	); // locked (padlock closed)
	customChars[6] = Array(14,16,16,31,27,27,31,0	); // unlocked (padlock open) 
	customChars[7] = Array(17,18,23,9,19,4,7,0		); // single-character "1/2"  
	
	for(var i=0;i<8;i++){	   
		for(var j=0;j<8;j++){	   
			data(customChars[i][j]);  
		}	
	}
}

function putstr(str){
	for(var i=0; i< str.length;i++){
		data(ascii.indexOf(str.charAt(i)));
	}


}

function DDRadrs(address){
	 instr(128 + address);
}

function CGRadrs(address){
	 instr(64 + address);
}

function mcl(x_times){
	if(arguments.length == 0){
		var x_times = 1;
	}
	for(var i=0; i < x_times;i++){
		instr(16);
	}
}

function mcr(x_times){
	if(arguments.length == 0){
		var x_times = 1;
	}
	for(var i=0; i < x_times;i++){
		instr(20);
	}
}
function sdl(x_times){
	if(arguments.length == 0){
		var x_times = 1;
	}
	for(var i=0; i < x_times;i++){
		instr(24);
	}
}

function sdr(x_times){
	if(arguments.length == 0){
		var x_times = 1
	}
	for(var i=0; i < x_times;i++){
		instr(28);
	}
}



function delay(lngth){
	var d= new Date();
	var prevTime = d.getTime();
	var currTime = d.getTime();
	while((currTime - prevTime) < lngth){
		var d= new Date();
		currTime = d.getTime();
	}
}

function scripter(script){
	//alert(script)
	var funcText = eval(script);
	funcText = funcText.toString();
	//alert(funcText)
	document.ctrl.scriptBox.value = funcText.substring(funcText.indexOf('{')+1,funcText.lastIndexOf('}')) ;

}

function odometer(){
	instr(12);
	instr(128+7);
	data(0);
	
	for(var i=0; i<9; i++){
		for(var m=0;m < 10;m++){
			instr(64);
			for(var j=m; j<8; j++){
				data(chrtbl[i+0x30][j])
			}
			for(var k=0; k<m; k++){
				data(chrtbl[i+0x31][k]);
			}
		}
	}
	
}



function instr(instrc){
	clearMsgs();	
	if((instrc & maskSetDDRAMadrs) == instrSetDDRAMadrs){
		setDDRadrs(instrc & 0x7f);
		lastAdrsSet = 'DDRAM';
		return;
	}
	
	if((instrc & maskSetCGRAMadrs) == instrSetCGRAMadrs){
		AC = (instrc & 0x3f)+64;
		updateUndCurs();
		lastAdrsSet = 'CGRAM';
		return;
	}
	
	if((instrc & maskFuncSet) == instrFuncSet){
		if(instrc & eithtBitMode){
			if(DL == 0){
				DL = 1;
				for(var i=0; i<4; i++){
					togImage('d'+i);
				}
			}
			DL = 1;
		}
		else{
			DL = 0;
			for(var i=0; i<4; i++){
				document['d'+i].src = 'b1t.gif';
			}
			var newVal = document.ctrl.lcdpinsDec.value >> 4;
			document.ctrl.lcdpinsHex.value = baseDisp(newVal,16);
			document.ctrl.lcdpinsDec.value = baseDisp(newVal,10);
		}
		
		if(instrc & twoLines){
			N = 1;
			range = 32;
			ln2On();
			updateDisp();
		}
		else{
			N = 0;
			range = 16;
			updateDisp();
			ln2Off();
			
		}
		
		if(instrc & largeFont){
			F = 1;
		}
		else{
			F = 0;
		}
		
		return;
	}
	
	if((instrc & maskCursorDisplay) == instrCursorDisplay){
		if(instrc & rightLeft){
			RL = 1;
		}
		else{
			RL = -1;
		}
		if(instrc & shiftOrCursorMove){
			SC = 1;
			shiftChars -=RL;
			lastAdrsSet = 'DDRAM';
			updateDisp();
		}
		else{
			SC = 0;
			lastAdrsSet = 'DDRAM';
			incdcrDDRadrs(RL);
			updateDisp();
		}

		return;
	}
	
	if((instrc & maskEntryMode) == instrEntryMode){
		if(instrc & incCursorPos){
			ID = 1;
		}
		else{
			ID = -1; 
		}
		
		if(instrc & scrollDisp){
			S = 1;
		}
		else{
			S = 0;
		}
		
		return;
	}
	
	if((instrc & maskDisplayCtrl) == instrDisplayCtrl){
		if(instrc & displayOn){
			D = 1;
			dispBlanked = 0;
			updateDisp();
		}
		else{
			D  = 0;
			updateDisp();
		}
		
		if(instrc & cursorOn){
			C = 1;
			updateUndCurs();
		}
		else{
			C  = 0;
			updateUndCurs();
		}
		
		if(instrc & blinkOn){
			B = 1;
		}
		else{
			B  = 0;
		}	
		
		return;
	}
		
	if((instrc & maskClearDisplay) == instrClearDisplay){
		for(var i=0; i<104;i++){
			DDRAM[i]=0x20;
		}
		ID = 1;
		setDDRadrs(0);
		lastAdrsSet = 'DDRAM';
		updateDisp();
		
		return;
	}

	if((instrc & maskCursorHome) == instrCursorHome){
		shiftChars = 0;
		setDDRadrs(0);
		lastAdrsSet = 'DDRAM';
		updateDisp();
		
		return;
	}	
	return;
}

