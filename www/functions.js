function sendCommandtoServer(cmd) {
	sendCommand = new XMLHttpRequest();
	sendCommand.open("GET", cmd, true);
	sendCommand.send(null);
}
// server command 0
function turnOffAll() {
	server="/arduino/light/0";
	sendCommandtoServer(server);
	window.setTimeout( sendCommandtoServer(server), 500 );
}

// to implement server command 1 - gives random colour
function randomColour() {
	server="/arduino/light/1";
	sendCommandtoServer(server);
	window.setTimeout( sendCommandtoServer(server), 500 );
}



// server command 2
function onePixel() {
	var red = $("#onePixelColorBoxRed").val();
	var green = $("#onePixelColorBoxGreen").val();
	var blue = $("#onePixelColorBoxBlue").val();
	var rgb = red + '/' + green + '/' + blue;
	var onePixelWait = $("#onePixelWait").val();
	server="/arduino/light/2/" + rgb + "/" + onePixelWait;
	sendCommandtoServer(server);
}
// server command 3
function randomLight() {
	server="/arduino/light/3";
	sendCommandtoServer(server);
}
// server command 4
function rainbowCycle() {
	var rainbowCycleWait = $("#rainbowCycleWait").val();
	server="/arduino/light/4/" + rainbowCycleWait;
	sendCommandtoServer(server);
}
// server command 6
function specificColor(r,g,b) {
	rgb = r + '/' + g + '/' + b;
	server="/arduino/light/6/" + rgb;
	sendCommandtoServer(server);
}
function applyColor() {
	var red = $( "#red" ).slider( "value" );
	var green = $( "#green" ).slider( "value" );
	var blue = $( "#blue" ).slider( "value" );
	specificColor( red, green, blue );
}


$(document).ready(function() {

$( "#tabs" ).tabs();

$("#solidColorPalette").spectrum( {
	preferredFormat: "rgb",
	showInput: true,
	showPalette: true,
	palette: [
	['rgb(255, 0, 0);', 'rgb(0, 255, 0);', 'rgb(0, 0, 255);'],
	['rgb(255, 128, 0);', 'hsv 100 70 50', 'lightyellow']
	],
	flat: true,

	change: function(color) {
		color.toRgb();
		redVal = Math.round(color._r);
		greenVal = Math.round(color._g);
		blueVal = Math.round(color._b);
		specificColor( redVal, greenVal, blueVal );
	}
});
$("#onePixelPalette").spectrum( {
	preferredFormat: "rgb",
	showInput: true,
	showPalette: true,
	palette: [
	['rgb(255, 0, 0);', 'rgb(0, 255, 0);', 'rgb(0, 0, 255);'],
	['rgb(255, 128, 0);', 'hsv 100 70 50', 'lightyellow']
	],
	flat: true,

	change: function(color) {
		color.toRgb();
		redVal = Math.round(color._r);
		greenVal = Math.round(color._g);
		blueVal = Math.round(color._b);
		$("#onePixelColorBoxRed").val(redVal);
		$("#onePixelColorBoxGreen").val(greenVal);
		$("#onePixelColorBoxBlue").val(blueVal);
	}
});
$( "#onepixel-slider" ).slider({
	range: "min",
	min: 0,
	max: 15000,
	value: 100,
	slide: function( event, ui ) {
		$( "#onePixelWait" ).val( ui.value );
	}
});
$( "#onePixelWait" ).val( $( "#onepixel-slider" ).slider( "value" ) );
$( "#rainbowcycle-slider" ).slider({
	range: "min",
	min: 0,
	max: 25,
	value: 5,
	slide: function( event, ui ) {
		$( "#rainbowCycleWait" ).val( ui.value );
	}
});
$( "#rainbowCycleWait" ).val( $( "#rainbowcycle-slider" ).slider( "value" ) );
});
