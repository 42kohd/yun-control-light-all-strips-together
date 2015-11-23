	function applyColor() {
		var red = $( "#red" ).slider( "value" );
		var green = $( "#green" ).slider( "value" );
		var blue = $( "#blue" ).slider( "value" );
		specificColor( red, green, blue );
	}
	function onePixel() {
		
		var red = $("#onePixelColorBoxRed").val();
		var green = $("#onePixelColorBoxGreen").val();
		var blue = $("#onePixelColorBoxBlue").val();
		var rgb = red + '/' + green + '/' + blue;
		var onePixelWait = $("#onePixelWait").val();
				
		server="/arduino/light/2/" + rgb + "/" + onePixelWait;
		sendCommand = new XMLHttpRequest();
		sendCommand.open("GET", server, true);
		sendCommand.send(null);
	}
	function randomLight() {
		server="/arduino/light/3";
		sendCommand = new XMLHttpRequest();
		sendCommand.open("GET", server, true);
		sendCommand.send(null);
	}
	function sendCommand(cmd) {
		sendCommand = new XMLHttpRequest();
		sendCommand.open("GET", cmd, true);
		sendCommand.send(null);
		
		}
	function turnOffAll() {
		server="/arduino/light/0";
		sendCommand(server);
		//sendCommand = new XMLHttpRequest();
		//sendCommand.open("GET", server, true);
		//sendCommand.send(null);
		window.setTimeout( sendCommand(server), 5000 ); // 5 seconds
	}
	
	function rainbowCycle() {
		var rainbowCycleWait = $("#rainbowCycleWait").val();
		server="/arduino/light/4/" + rainbowCycleWait;
		sendCommand = new XMLHttpRequest();
		sendCommand.open("GET", server, true);
		sendCommand.send(null);
	}	
	function changeProgram(programChoose) {
		server="/arduino/light/" + programChoose;
		sendCommand = new XMLHttpRequest();
		sendCommand.open("GET", server, true);
		sendCommand.send(null);
	}
	function specificColor(r,g,b) {
		rgb = r + '/' + g + '/' + b;
		server="/arduino/light/6/" + rgb;
		sendCommand = new XMLHttpRequest();
		sendCommand.open("GET", server, true);
		sendCommand.send(null);
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
