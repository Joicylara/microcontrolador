document['p0'].src='0.gif'
document['p1'].src='14.gif'
document['p2'].src='17.gif'
document['p3'].src='1.gif'
document['p4'].src='2.gif'
document['p5'].src='4.gif'
document['p6'].src='8.gif'
document['p7'].src='31.gif'



 31, 2, 4, 8,16,17,14, 0,
 31, 2, 4, 8,16,17,14, 0,
  0,14,17,16, 8, 4, 2,31,
   0,14,17, 1, 2, 4, 8,31,
14,17,19,21,25,17,14, 0,


/*
 * LCD Command "Set Display Data RAM Address" = 10000000
 */

var cmdSetDdram  = 0x80;
var maskSetDdram = 0x80;

/*
 * LCD Command "Set Display Character Generator RAM Address" = 01aaaaaa
 */

var cmdSetCgram  = 0x40;
var maskSetCgram = 0xc0;


/*
 * LCD Command Function Set =  001dnfxx
 *  d = 1 for 8-bit interface or 0 for 4-bit interface
 *  n = for 2 line displays, n=1 allows both lines to be displayed
 *      while n=0 only allows the first.
 * f = font size. f=1 is for 5x11 dots while f=0 is for 5x8 dots.
 */

var cmdFuncSet  = 0x20;    // LCD Command "Function Set"
var maskFuncSet = 0xe0;    // 
var 4BitMode     = 0x00;    // d=0
var 8BitMode     = 0x10;    // d=1
var 1Line        = 0x00;    // n=0
var 2Lines       = 0x08;    // n=1
var SmallFont    = 0x00;    // f=0
var LargeFont    = 0x04;    // f=1

/*
 * LCD Command "Cursor Display" = 0001sdxx
 *  s = 1 Sets cursor-move or display-shift
 *  d = 1 Shift right 0 = shift left
 */

var cmdCursorDisplay   = 0x10;   // LCD Command "Cursor Display"
var maskCursorDisplay  = 0xf0;   // 

/*
 * LCD Command Display Control = 00001dcb
 *  d = 1 turn display on or 0 to turn display off
 *  c = 1 turn cursor on or 0 to turn cursor off
 *  b = 1 blinking cursor or 0 non-blinking cursor
 */

var cmdDisplayCtrl  = 0x08;    // LCD Command "Display Control"
var maskDisplayCtrl = 0xf8;    // 
var DisplayOff       = 0x00;    // d=0
var DisplayOn        = 0x04;    // d=1
var cursorOff        = 0x00;    // c=0
var cursorOn         = 0x02;    // c=1
var BlinkOff         = 0x00;    // b=0
var BlinkOn          = 0x01;    // b=1


/*
 * LCD Command "Entry Mode" = 000001is
 *  i = 1 to increment or 0 to decrement the DDRAM address after each DDRAM access.
 *  s = 1 to scroll the display in the direction specified by the i-bit when the
 *       cursor reaches the edge of the display window.
 */

var cmdEntryMode  = 0x04;    // LCD Command "Entry Mode"
var maskEntryMode = 0xfc;    // 
var DecCursorPos  = 0x00;    // i=0
var IncCursorPos  = 0x02;    // i=1
var NoScroll      = 0x00;    // s=0
var Scroll        = 0x01;    // s=1

/*
 * LCD Command "Cursor Home" = 0000001x
 */

var cmdCursorHome   = 0x02;   // LCD Command "Cursor Home"
var maskCursorHome  = 0xfe;   // 

// LCD Command Clear Display = 00000001
var cmdClearDisplay  = 0x01;
var maskClearDisplay = 0xff;


function updateDisp(DDRAMChanged,Shift){
	if(D==0){
		return 
	}
	if(S){
		shiftChars += -1
	}
	
	for(var ln=0; ln<16; ln++){
		if(currDispChrs[ln] != DDRAM[ln + 40 - shiftChars]){
			pchr(DDRAM[ln + 40 - shiftChars],ln)
			currDispChrs[i] = DDRAM[ln + 40 - shiftChars]
			cursPos = ln+1
			blinkChar = DDRAM[ln + 40 - shiftChars+1]
		}
	}
	for(var ln=16; ln<32; ln++){
		if(currDispChrs[ln] != DDRAM[ln + 48 + 40 - shiftChars]){
			pchr(DDRAM[ln + 48 + 40 - shiftChars],ln)
			currDispChrs[i] = DDRAM[ln + 48 + 40 - shiftChars]
			cursPos = ln+1
			blinkChar = DDRAM[ln + 48 + 40 - shiftChars+1]
			//alert(DDRAM[ln + 48],ln)
		}
	}
	
	
	
}


	if(DDRAMadrs >= 0x40){
		cursPos = DDRAMadrs  + 48 + offset
		blinkChar = DDRAM[cursPos + 48 + offset]
	}else{
		currDispChrs[i][adrs]
		cursPos = DDRAMadrs  + offset
		blinkChar = DDRAM[cursPos + offset]
	}


/*if(C == 0 || D == 0 || cursPos < 0 || cursPos > 31){
		document['p'+ parseInt(cursPos * 8 + 7)].src = '0.gif'
		return
	}*/


function pchr(chrnum, pos){
	var pos = pos * 8 
	for(i=0;i<7;i+=1){
		document['p'+ parseInt(pos+i)].src = chrtbl[chrnum][i]+'.gif'
	}
	
	if(chrnum < 8){
		document['p'+ parseInt(pos+7)].src = chrtbl[chrnum][7]+'.gif'
	}else{
		document['p'+ parseInt(pos+7)].src = '0.gif'
	}
}


function updateDisp(DDRAMChanged,Shift){

	if(D==0){
		if(dispBlanked != 1){
			blankDisp();
		}
		return 
	}

	if(shiftChars > 39 || shiftChars < -39)
		shiftChars=0
	for(var i=0; i<16; i++){ 
		if(shiftChars < 0){
			currDispChrs[i][adrs]= (i + 40 + shiftChars) % 40	//adrs
		}else{
			currDispChrs[i][adrs]= (i + 40 + shiftChars) % 40	//adrs
		}
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
	for(var ln=0; ln<32; ln++){
		if(currDispChrs[ln][chr] != DDRAM[currDispChrs[ln][adrs]]){
			pchr(DDRAM[currDispChrs[ln][adrs]],ln)
			currDispChrs[ln][chr] = DDRAM[currDispChrs[ln][adrs]]
			cursPos = DDRAM[currDispChrs[ln][adrs]]
			blinkChar = DDRAM[currDispChrs[ln][adrs] + 1]
		}
	}
	updateUndCurs()
}





function updateUndCurs(){
	var range = 0
	if(N == 0){
		range = 16
	}
	else{
		range = 32
	}
	
	var adrs = 1 
	var chr = 0
	if(D != 0){
		for(var i=0; i<range; i++){
			if(currDispChrs[i][adrs] == prevDDRAMadrCursAt){
				pchr(DDRAM[currDispChrs[prevcursPos][adrs]],prevcursPos)
			}	
		}
	}
		
	for(var i=0; i<range; i++){
		if(currDispChrs[i][adrs] == DDRAMadrs){
			prevDDRAMadrCursAt = DDRAMadrs
			cursPos = i
			prevcursPos = i
			blinkChar = currDispChrs[i][chr]
		}	
	}
	
	if(C == 1){
		document['p'+ parseInt(cursPos * 8 + 7)].src = '31.gif'
	}
	
}


function incdcrDDRadrs(incordcr){
	//alert(incordcr)
	if(incordcr == 1){
		if(N == 0){
			DDRAMadrs += 1
			DDRAMadrs %= 80
			DDRptr = DDRAMadrs
		}
		else{
			DDRAMadrs += 1
			DDRptr = DDRAMadrs
			if(DDRAMadrs > 39 && DDRAMadrs < 64){
				DDRAMadrs = 64
				DDRptr = 39
			}
			if(DDRAMadrs > 103){
				DDRAMadrs = 0
				DDRptr = 0
			}
		}
	}
	else{
		//alert('ddradrs decreasing !' + DDRAMadrs)
		if(N == 0){
			DDRAMadrs -= 1
			if(DDRAMadrs < 0){DDRAMadrs = 79}
			DDRAMadrs %= 80
			DDRptr = DDRAMadrs
		}
		else{
			DDRAMadrs -= 1
			DDRptr = DDRAMadrs
			if(DDRAMadrs < 0){
				DDRAMadrs = 103
				DDRptr = 79
			}
			if(DDRAMadrs > 39 && DDRAMadrs < 64){
				DDRAMadrs = 64
				DDRptr = 39
			}
		}
	}
	
	
	//if(DDRAMadrs < 0 || (DDRAMadrs > 39 && DDRAMadrs < 64) || DDRAMadrs >= 104){alert('DDRAMadrs invalid !!!! >>>>'+ DDRAMadrs)}
}
