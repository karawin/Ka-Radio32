var content = "Content-type",
	ctype = "application/x-www-form-urlencoded",
	cjson = "application/json";
var auto,intervalid , intervalrssi  , timeid, websocket,urlmonitor , e, moniPlaying = false,editPlaying = false, editIndex= 0 ,curtab = "tab-content1",stchanged = false,maxStation = 255,themeIn = "0";
const karadio = "Karadio32";
const working = "Working.. Please Wait";

function openwebsocket(){	
//	autoplay(); //to force the server socket to accept and open the web server client.
	websocket = new WebSocket("ws://"+window.location.host+"/");
	console.log("url:"+"ws://"+window.location.host+"/");


	websocket.onmessage = function (event) {
	try{	
		console.log("onmessage:"+event.data);
	    var arr = JSON.parse(event.data);		
		if (arr["meta"] == "") 
		{ document.getElementById('meta').innerHTML = karadio;setMainHeight(curtab);}
		if (arr["meta"]) 
			{	document.getElementById('meta').innerHTML = arr["meta"].replace(/\\/g,"");
				setMainHeight(curtab);
			}
		changeTitle(document.getElementById('meta').innerHTML);
		if (arr["wsvol"]) onRangeVolChange(arr['wsvol'],false); 
		if (arr["lsleep"]) labelSleep(arr["lsleep"]); 
		if (arr["lwake"]) labelWake(arr["lwake"]); 
		if (arr["wsicy"]) icyResp(arr["wsicy"]); 
		if (arr["wssound"]) soundResp(arr["wssound"]); 
		if (arr["monitor"]) playMonitor(arr["monitor"]); 
		if (arr["wsstation"]) wsplayStation(arr["wsstation"]); 
		if (arr["wsrssi"]) {document.getElementById('rssi').innerHTML = arr["wsrssi"]+' dBm';setTimeout(wsaskrssi,5000);}
		if (arr["upgrade"]) {document.getElementById('updatefb').innerHTML = arr["upgrade"];}
		if (arr["iurl"]) {document.getElementById('instant_url').value  = arr["iurl"];buildURL();}
		if (arr["ipath"]) {document.getElementById('instant_path').value = arr["ipath"];buildURL();}
		if (arr["iport"]) {document.getElementById('instant_port').value = arr["iport"];buildURL();}
	} catch(e){ console.log("error"+e);}
}

	websocket.onopen = function (event) {
		console.log("Open, url:"+"ws://"+window.location.host+"/");
		if(window.timerID){ /* a setInterval has been fired */
			window.clearInterval(window.timerID);
			window.timerID=0;
		}
		setTimeout(wsaskrssi, 5000); // start the rssi display
		websocket.send("opencheck");
	}
	websocket.onclose = function (event) {
		console.log("onclose code: "+event.code);
		console.log("onclose reason: "+event.reason);
		if(!window.timerID){ /* avoid firing a new setInterval, after one has been done */
		window.timerID=setInterval(function(){checkwebsocket()}, 1500);
		}	
	}	
	websocket.onerror = function(event) {
	// handle error event
		console.log("onerror reason: "+event.reason);
		websocket.close();
	}
}

// Change the title of the page
function changeTitle($arr) {
    window.parent.document.title = $arr; // on change l'attribut <title>
}

// ask for the rssi and restart the timer
function wsaskrssi(){
	try{
			websocket.send("wsrssi &");	
	} catch(e){ console.log("error"+e);}
}

function wsplayStation($arr){
	var i;
	select = document.getElementById('stationsSelect');
	opt = select.options;
	for (i=0; i< maxStation;i++)
	{
		id = opt[i].value.split(":");
		id = id[0];
		if (id == $arr) break;
	}
	if (i == maxStation) i = 0;
	select.selectedIndex = i;
}

function playMonitor($arr){
	urlmonitor = "";
	urlmonitor = $arr;	
	if (moniPlaying)
	{
		monitor = document.getElementById("audio");	
		if (urlmonitor.endsWith("/"))
			var src = urlmonitor+ ";";
		else 	src = urlmonitor;
		monitor.src = src;
		monitor.play();
	}
}	
function mplay(){
	monitor = document.getElementById("audio");
	if (urlmonitor.endsWith("/"))
		var src = urlmonitor + ";";
	else 	src = urlmonitor;
	monitor.src = src;
	monitor.volume = document.getElementById("volm_range").value / 100;
	while (monitor.networkState == 2);
	monitor.play();
	moniPlaying = true;	
	monitor.muted = false;
}	

function monerror()
{
		monitor = document.getElementById("audio");
		console.log("monitor error1 "+ monitor.error.code);
}	
function mstop(){
		monitor = document.getElementById("audio");	
		monitor.muted = true;
		monitor.src = 'http://karadio.karawin.fr/silence-1sec.mp3';
		moniPlaying = false;
}	
function mpause(){
		monitor = document.getElementById("audio");	
		monitor.pause();
}	
function mvol($val){
	monitor = document.getElementById("audio");
	monitor.volume= $val;
}	

function checkwebsocket() {
	if (typeof websocket == 'undefined') openwebsocket();	
	else 
	{
		if (websocket.readyState == websocket.CLOSED) openwebsocket();	
		else if (websocket.readyState == websocket.OPEN) websocket.send("opencheck");
	}	
}	

//check for a valid ip	
function chkip($this)
{
  if ( /^([0-9]+\.){3}[0-9]+$/.test($this.value) ) $this.style.color = "green";
  else $this.style.color = "red";
}  

function clickdhcp() {
  if (document.getElementById("dhcp").checked)
  {
    document.getElementById("ip").setAttribute("disabled","") ;
    document.getElementById("mask").setAttribute("disabled","") ;
    document.getElementById("gw").setAttribute("disabled","") ;
  } else {
      document.getElementById("ip").removeAttribute("disabled") ;
      document.getElementById("mask").removeAttribute("disabled") ;
      document.getElementById("gw").removeAttribute("disabled") ;
  }
}  
function clickdhcp2() {
  if (document.getElementById("dhcp2").checked)
  {
    document.getElementById("ip2").setAttribute("disabled","") ;
    document.getElementById("mask2").setAttribute("disabled","") ;
    document.getElementById("gw2").setAttribute("disabled","") ;
  } else {
      document.getElementById("ip2").removeAttribute("disabled") ;
      document.getElementById("mask2").removeAttribute("disabled") ;
      document.getElementById("gw2").removeAttribute("disabled") ;
  }
}  


function valid() {
	wifi(1);
    alert("System reboot. Please change your browser address to the new one.");
}

function validOutput() {
	hardware(1);
    alert("System reboot.");
}

function scrollTo(to, duration) {
    if (duration < 0) return;
    var scrollTop = document.body.scrollTop + document.documentElement.scrollTop;
    var difference = to - scrollTop;
    var perTick = difference / duration * 10;

    setTimeout(function() {
      scrollTop = scrollTop + perTick;
      document.body.scrollTop = scrollTop;
      document.documentElement.scrollTop = scrollTop;
      if (scrollTop === to) return;
      scrollTo(to, duration - 10);
    }, 10);
  }

// go to top
function wtop() {
//	window.scrollTo(0, 0);
	scrollTo(0,200);
}

// display current time
function dtime() {
	var d = new Date(), elt = document.getElementById('sminutes'),eltw = document.getElementById('wminutes');
//	document.getElementById("time").innerHTML = d.toLocaleTimeString();	
	udate = d.toTimeString().split(" ");
	document.getElementById("time").innerHTML = udate[0];	
	if ((!isNaN(elt.innerHTML))&&(elt.innerHTML != "0") )
		--elt.innerHTML;
	if ((!isNaN(elt.innerHTML))&&(elt.innerHTML == 0)) elt.innerHTML = "0";
	if ((!isNaN(eltw.innerHTML))&&(eltw.innerHTML != "0") )
		--eltw.innerHTML;
	if ((!isNaN(eltw.innerHTML))&&(eltw.innerHTML == 0)) eltw.innerHTML = "0";
}
// return the timezone (+/-x)
function timezone(offset) {
    var minutes = Math.abs(offset);
    var hours = Math.floor(minutes / 60);
	minutes = Math.abs(offset%60);
    var prefix = offset < 0 ? "+" : "-";
//	document.getElementById('atzo').innerHTML = prefix+hours+":"+minutes;	
    return prefix+hours+":"+minutes;	
}

function labelSleep(label){
	document.getElementById('sminutes').innerHTML = label;	
}
function sleepup(e)
{
	if (e.keyCode == 13) startSleep();
}
function startSleep(){
	var valm,h0,h1;
	var cur = new Date();
	var hop = document.getElementById("sleepdelay").value.split(":");
	h0 = parseInt(hop[0],10);
	h1 = parseInt(hop[1],10);
	if(!isNaN(h0)){
		if (!isNaN(h1)) // time mode
		{
			fut = new Date(cur.getFullYear(),cur.getMonth(), cur.getDate(),h0,h1,0 );
			if (fut.getTime() > cur.getTime())
				valm = Math.round((fut.getTime() - cur.getTime())/60000) ; //seconds
			else valm = 1440 - Math.round((cur.getTime() - fut.getTime())/60000) ; //seconds
			if (valm == 0)
			if (fut.getTime() > cur.getTime() )   valm = 1; // 1 minute mini
			else valm = 1440;
		} else valm = h0; // minute mode
		websocket.send("startSleep=" +valm +"&");
//		labelSleep("Started, Good night!");
//		window.setTimeout(labelSleep, 2000 ,(valm*60)-2);	
	} else
	{
		labelSleep("Error, try again");
		window.setTimeout(labelSleep, 2000 ,"0");
	}	
}

function stopSleep(){
	var a = document.getElementById("sleepdelay").value;
    websocket.send("stopSleep");
    labelSleep("0");
//    window.setTimeout(labelSleep, 2000, a);	
}

function labelWake(label){
	document.getElementById('wminutes').innerHTML = label;	
}
function wakeup(e)
{
	if (e.keyCode == 13) startWake();
}
function startWake(){
	var valm,h0,h1;
	var cur = new Date();
	var hop = document.getElementById("wakedelay").value.split(":");
	h0 = parseInt(hop[0],10);
	h1 = parseInt(hop[1],10);
	if(!isNaN(h0)){
		if (!isNaN(h1)) // time mode
		{
			fut = new Date(cur.getFullYear(),cur.getMonth(), cur.getDate(),h0,h1,0 );
			if (fut.getTime() > cur.getTime())
				valm = Math.round((fut.getTime() - cur.getTime())/60000) ; //seconds
			else valm = 1440 - Math.round((cur.getTime() - fut.getTime())/60000) ; //seconds
			if (valm == 0)
			if (fut.getTime() > cur.getTime() )   valm = 1; // 1 minute mini
			else valm = 1440;
		} else valm = h0; // minute mode
		websocket.send("startWake=" +valm +"&");
//		labelWake("Started");
//		window.setTimeout(labelWake, 2000 ,(valm*60)-2);	
	} else
	{
		labelWake("Error, try again");
		window.setTimeout(labelWake, 2000 ,"0");
	}	
}

function stopWake(){
	var a = document.getElementById("wakedelay").value;
    websocket.send("stopWake");
    labelWake("0");
}



function promptworking(label) {
	document.getElementById('meta').innerHTML = label;
	if (label == "") {
		document.getElementById('meta').innerHTML = karadio;
//		refresh();
	}
}

function saveTextAsFile()
{
	var output = '',id,textFileAsBlob,downloadLink,fileName; 
//	for (var key in localStorage) {
	for (id =0;id<maxStation ;id++) {
//	output = output+(localStorage[key])+'\n';
	output = output+(localStorage[id])+'\n';
	}
	fileName = document.getElementById('filesave').value;
	if (fileName == "")
		alert("Please give a file name");
	else {	
		textFileAsBlob = new Blob([output], {type:'text/plain'}),
		downloadLink =  document.createElement("a");
		downloadLink.style.display = "none";
		downloadLink.setAttribute("download", fileName);
		document.body.appendChild(downloadLink);

		if(window.navigator.msSaveOrOpenBlob)
			downloadLink.addEventListener("click",function(){
                window.navigator.msSaveBlob(textFileAsBlob, fileName);
            });
		else	if ('URL' in window)
			downloadLink.href = window.URL.createObjectURL(textFileAsBlob);
		else 	
				downloadLink.href = window.webkitURL.createObjectURL(textFileAsBlob);
		downloadLink.click();
	}
}

function full(){
	if (document.getElementById('Full').checked)
	{
		if ((document.getElementById('not1').innerHTML =="")&& (document.getElementById('not1').innerHTML ==""))	
			document.getElementById('lnot1').style.display = "none";
			else 	document.getElementById('lnot1').style.display = "inline-block";	
			
		if (document.getElementById('bitr').innerHTML =="")
			document.getElementById('lbitr').style.display = "none";
			else 	document.getElementById('lbitr').style.display = "inline-block";
			
		if (document.getElementById('descr').innerHTML =="")
			document.getElementById('ldescr').style.display = "none";
			else 	document.getElementById('ldescr').style.display = "inline-block";		

		if (document.getElementById('genre').innerHTML =="")
			document.getElementById('lgenre').style.display = "none";
			else 	document.getElementById('lgenre').style.display = "inline-block";	
			
	} else
	{
		document.getElementById('lnot1').style.display = "none";	
		document.getElementById('lbitr').style.display = "none";
		document.getElementById('ldescr').style.display = "none";
		document.getElementById('lgenre').style.display = "none";
	}
	setMainHeight("tab-content1");
}
	
function icyResp(arr) {			
			document.getElementById('curst').innerHTML = arr["curst"].replace(/\\/g,"");
			select = document.getElementById('stationsSelect');
			opt = select.options;
			for (i=0; i< maxStation;i++)
			{
				id = opt[i].value.split(":");
				id = id[0];
				if (id == document.getElementById('curst').innerHTML) break;
			}
			if (i == maxStation) i = 0;
			select.selectedIndex = i;				
			if ((arr["descr"] =="")||(!document.getElementById('Full').checked))
				document.getElementById('ldescr').style.display = "none";
			else 	document.getElementById('ldescr').style.display = "inline-block";
			document.getElementById('descr').innerHTML = arr["descr"].replace(/\\/g,"");			
			document.getElementById('name').innerHTML = arr["name"].replace(/\\/g,"");
			if ((arr["bitr"] =="")||(!document.getElementById('Full').checked)){	document.getElementById('lbitr').style.display = "none";}
			else 	document.getElementById('lbitr').style.display = "inline-block";
			document.getElementById('bitr').innerHTML = arr["bitr"].replace(/\\/g,"") + " kB/s";
			if (arr["bitr"] =="") document.getElementById('bitr').innerHTML="";
			if (((arr["not1"] =="")&& (arr["not2"] ==""))||(!document.getElementById('Full').checked))	document.getElementById('lnot1').style.display = "none";
			else 	document.getElementById('lnot1').style.display = "inline-block";	
			document.getElementById('not1').innerHTML = arr["not1"].replace(/\\/g,"").replace(/^<BR>/,"");
			document.getElementById('not2').innerHTML = arr["not2"].replace(/\\/g,"");
			if ((arr["genre"] =="")||(!document.getElementById('Full').checked))
				document.getElementById('lgenre').style.display = "none";
			else 	document.getElementById('lgenre').style.display = "inline-block";	
			document.getElementById('genre').innerHTML = arr["genre"].replace(/\\/g,"");
			if ((arr["url1"] =="")||(arr["url1"] ==" "))
			{	
				document.getElementById('lurl').style.display = "none";
				document.getElementById('icon').style.display = "none";
			}	
			else 
			{	
				document.getElementById('lurl').style.display = "inline-block";
				document.getElementById('icon').style.display = "inline-block";
				$url = arr["url1"].replace(/\\/g,"").replace(/ /g,"");
				if ($url == 'http://www.icecast.org/') 
					document.getElementById('icon').src = "/logo.png";
				else
				document.getElementById('icon').src =  "http://www.google.com/s2/favicons?domain_url="+$url;
			}	
			$url = arr["url1"].replace(/\\/g,"");
			document.getElementById('url1').innerHTML = $url;
			document.getElementById('url2').href = $url;
			if (arr["meta"] == "") 
				{ document.getElementById('meta').innerHTML = karadio;setMainHeight(curtab);}			
			if (arr["meta"]) document.getElementById('meta').innerHTML = arr["meta"].replace(/\\/g,"");
			changeTitle(document.getElementById('meta').innerHTML);
            if (typeof arr["auto"] != 'undefined')  // undefined for websocket
			if (arr["auto"] == "1")
				document.getElementById("aplay").setAttribute("checked","");
			else
				document.getElementById("aplay").removeAttribute("checked") ;
			setMainHeight(curtab); 
}	
function soundResp(arr) {			
			document.getElementById('vol_range').value = arr["vol"].replace(/\\/g,"");
			document.getElementById('treble_range').value = arr["treb"].replace(/\\/g,"");
			document.getElementById('bass_range').value = arr["bass"].replace(/\\/g,"");
			document.getElementById('treblefreq_range').value = arr["tfreq"].replace(/\\/g,"");
			document.getElementById('bassfreq_range').value = arr["bfreq"].replace(/\\/g,"");
			document.getElementById('spacial_range').value = arr["spac"].replace(/\\/g,"");
			onRangeVolChange(document.getElementById('vol_range').value,false);
			onRangeChange('treble_range', 'treble_span', 1.5, false,true);
			onRangeChange('bass_range', 'bass_span', 1, false,true);
			onRangeChangeFreqTreble('treblefreq_range', 'treblefreq_span', 1, false,true);
			onRangeChangeFreqBass('bassfreq_range', 'bassfreq_span', 10, false,true);
			onRangeChangeSpatial('spacial_range', 'spacial_span', true);
}	
function refresh() {
	xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && xhr.status == 200) {
			try{
				var arr = JSON.parse(xhr.responseText);
				icyResp(arr);
				soundResp(arr);
			} catch(e){console.log("error"+e);}
		}
	}
	try{	
		xhr.open("POST","icy",false);
		xhr.setRequestHeader(content,cjson);
		xhr.send();
		websocket.send("monitor");
	} catch(e){console.log("error"+e);}
}
// change the theme
function theme(){
	websocket.send("theme");
	window.location.reload(true); // force reload from the server
}

function resetEQ() {
	document.getElementById('treble_range').value = 0;
	onRangeChange('treble_range', 'treble_span', 1.5, false);
	document.getElementById('bass_range').value = 0;	
	onRangeChange('bass_range', 'bass_span', 1, false);
	document.getElementById('treblefreq_range').value = 1;
	onRangeChangeFreqTreble('treblefreq_range', 'treblefreq_span', 1, false);
	document.getElementById('bassfreq_range').value = 2;
	onRangeChangeFreqBass('bassfreq_range', 'bassfreq_span', 10, false);
	document.getElementById('spacial_range').value = 0;
	onRangeChangeSpatial('spacial_range', 'spacial_span');
}

function onRangeChange($range, $spanid, $mul, $rotate, $nosave) {
	var val = document.getElementById($range).value;
	if($rotate) val = document.getElementById($range).max - val;
	document.getElementById($spanid).innerHTML = (val * $mul) + " dB";
	if( typeof($nosave) == 'undefined' )saveSoundSettings();
}
function onRangeChangeFreqTreble($range, $spanid, $mul, $rotate, $nosave) {
	var val = document.getElementById($range).value;
	if($rotate) val = document.getElementById($range).max - val;
	document.getElementById($spanid).innerHTML = "From "+(val * $mul) + " kHz";
	if( typeof($nosave) == 'undefined' )saveSoundSettings();
}
function onRangeChangeFreqBass($range, $spanid, $mul, $rotate, $nosave) {
	var val = document.getElementById($range).value;
	if($rotate) val = document.getElementById($range).max - val;
	document.getElementById($spanid).innerHTML = "Under "+(val * $mul) + " Hz";
	if( typeof($nosave) == 'undefined' )saveSoundSettings();
}
function onRangeChangeSpatial($range, $spanid, $nosave) {
	var val = document.getElementById($range).value,
	 label;
	switch (val){
		case '0': label="Off";break;
		case '1': label="Minimal";break;
		case '2': label="Normal";break;
		case '3': label="Maximal";break;	
	}
	document.getElementById($spanid).innerHTML = label;
	if( typeof($nosave) == 'undefined' )saveSoundSettings();
}
function logValue(value) {
//Log(128/(Midi Volume + 1)) * (-10) * (Max dB below 0/(-24.04))
	var log = Number(value )+ 1;
	var val= Math.round((Math.log10(255/log) * 105.54571334));
	return val;
}

function onRangeVolChange($value,$local) {
	var value = logValue($value);
	document.getElementById('vol1_span').innerHTML = (value * -0.5) + " dB";
	document.getElementById('vol_span').innerHTML = (value * -0.5) + " dB";
	document.getElementById('vol_range').value = $value;
	document.getElementById('vol1_range').value = $value;
	if ($local)	
	{
		xhr = new XMLHttpRequest();
		xhr.open("POST","soundvol",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send(  "vol=" + $value+"&");
	}
}
function wifi(valid) {
	xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && xhr.status == 200) {	
			var arr = JSON.parse(xhr.responseText);
			document.getElementById('ssid').value = arr["ssid"];
			document.getElementById('passwd').value = "*Hidden*";
			document.getElementById('ssid2').value = arr["ssid2"];
			document.getElementById('passwd2').value ="*Hidden*";
			document.getElementById('ip').value = arr["ip"];
			chkip(document.getElementById('ip'));
			document.getElementById('mask').value = arr["msk"];
			chkip(document.getElementById('mask'));
			document.getElementById('gw').value = arr["gw"];
			chkip(document.getElementById('gw'));
			document.getElementById('ip2').value = arr["ip2"];
			chkip(document.getElementById('ip2'));
			document.getElementById('mask2').value = arr["msk2"];
			chkip(document.getElementById('mask2'));
			document.getElementById('gw2').value = arr["gw2"];
			chkip(document.getElementById('gw2'));
			document.getElementById('ua').value = arr["ua"];
			document.getElementById('host').value = arr["host"];
			document.getElementById('tzo').value = arr["tzo"];
			if (arr["dhcp"] == "1")
				document.getElementById("dhcp").setAttribute("checked","");
			else
				document.getElementById("dhcp").removeAttribute("checked") ;
			if (arr["dhcp2"] == "1")
				document.getElementById("dhcp2").setAttribute("checked","");
			else
				document.getElementById("dhcp2").removeAttribute("checked") ;
			document.getElementById('Mac').innerHTML = arr["mac"];
			clickdhcp();
			clickdhcp2();
		}
	}
	xhr.open("POST","wifi",false);
	xhr.setRequestHeader(content,ctype);
	xhr.send("valid=" + valid 
	+"&ssid=" + encodeURIComponent(document.getElementById('ssid').value )
	+ "&pasw=" + encodeURIComponent( document.getElementById('passwd').value) 
	+"&ssid2=" + encodeURIComponent(document.getElementById('ssid2').value) 
	+ "&pasw2=" + encodeURIComponent(document.getElementById('passwd2').value) 
	+ "&ip=" + document.getElementById('ip').value
	+"&msk=" + document.getElementById('mask').value
	+"&gw=" + document.getElementById('gw').value
	+"&ip2=" + document.getElementById('ip2').value
	+"&msk2=" + document.getElementById('mask2').value
	+"&gw2=" + document.getElementById('gw2').value
	+"&ua=" + encodeURIComponent(document.getElementById('ua').value) 
	+"&host=" + encodeURIComponent(document.getElementById('host').value) 
	+"&tzo=" + (document.getElementById('tzo').value) 
	+"&dhcp=" + document.getElementById('dhcp').checked
	+"&dhcp2=" + document.getElementById('dhcp2').checked+"&");
	
}
function hardware(valid) {
	var i,coutput;
	xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && xhr.status == 200) {	
			var arr = JSON.parse(xhr.responseText);
			document.getElementById("output"+arr['coutput']).checked = true;
			if (arr['coutput'] != "4") 
			{
				document.getElementById("vs1052Only").style.display = "none";
			}
			else {
				document.getElementById("vs1052Only").style.display = "run-in";
			}
		}
	}
	xhr.open("POST","hardware",false);
	xhr.setRequestHeader(content,ctype);
	for (i=0 ;i<6;i++) if (document.getElementById('output'+i).checked) break;
	if (i==6) coutput = 0;
	xhr.send("valid=" + valid 
	+"&coutput=" + i
	+"&");
}
function instantPlay() {
	var curl;
	try{
		xhr = new XMLHttpRequest();
		xhr.open("POST","instant_play",false);
		xhr.setRequestHeader(content,ctype);
		curl = document.getElementById('instant_path').value;
		if (!(curl.substring(0, 1) === "/")) curl = "/" + curl;
//		document.getElementById('instant_url').value = document.getElementById('instant_url').value.replace(/^https?:\/\//,'');
		curl = fixedEncodeURIComponent (curl);
		xhr.send("url=" + document.getElementById('instant_url').value + "&port=" + document.getElementById('instant_port').value + "&path=" + curl+"&");
	} catch(e){console.log("error"+e);}
}

function buildAddURL()
{
	
	if (document.getElementById('add_path').value == "") 
		  document.getElementById('add_path').value= "/";
	var str = document.getElementById('add_url').value;
	if (str.toLowerCase().startsWith('https', 0))
	{
		if (document.getElementById('add_port').value == "") 
		  document.getElementById('add_port').value= "443";
		document.getElementById('add_URL').value = document.getElementById('add_url').value+':'+
			document.getElementById('add_port').value + document.getElementById('add_path').value;
	}
	else 
	{
		if (document.getElementById('add_port').value == "") 
		  document.getElementById('add_port').value= "80";
		document.getElementById('add_URL').value = "http://"+document.getElementById('add_url').value+':'+
			document.getElementById('add_port').value + document.getElementById('add_path').value;
	}
}

function buildURL()
{

	if (document.getElementById('instant_path').value == "") 
		  document.getElementById('instant_path').value= "/";
	var str = document.getElementById('instant_url').value;
	if (str.toLowerCase().startsWith('https', 0))
	{
		if (document.getElementById('instant_port').value == "") 
		  document.getElementById('instant_port').value= "443";
		document.getElementById('instant_URL').value = document.getElementById('instant_url').value+':'+
			document.getElementById('instant_port').value + document.getElementById('instant_path').value;
	}
	else 
	{
		if (document.getElementById('instant_port').value == "") 
		  document.getElementById('instant_port').value= "80";
		document.getElementById('instant_URL').value = "http://"+document.getElementById('instant_url').value+':'+
			document.getElementById('instant_port').value + document.getElementById('instant_path').value;
	}
}

function parseEditURL()
{
	 var a = document.createElement('a');
	 a.href = document.getElementById('add_URL').value;
	 if (a.href.toLowerCase() !=location.hostname)
	 {
		if (a.href.startsWith("https"))
			document.getElementById('add_url').value = "https://"+a.hostname;
		else
			document.getElementById('add_url').value = a.hostname;	 
	 }
	 else
	 {
		if (!a.href.toLowerCase().startsWith("https"))
			document.getElementById('add_URL').value = "http://"+document.getElementById('add_URL').value;
		a.href = document.getElementById('add_URL').value;
		document.getElementById('add_url').value = a.hostname;
	}
	if (a.port == "")
		if (a.href.toLowerCase().startsWith("https"))
			document.getElementById('add_port').value = "443";
		else
			document.getElementById('add_port').value = "80";
	else document.getElementById('add_port').value = a.port;
	document.getElementById('add_path').value = a.pathname+a.search+a.hash;	 
}

function parseInstantURL()
{
	 var a = document.createElement('a');	 
	 a.href = document.getElementById('instant_URL').value;
	 if (a.href.toLowerCase() !=location.hostname)
	 {
		if (a.href.startsWith("https"))
			document.getElementById('instant_url').value = "https://"+a.hostname;
		else
			document.getElementById('instant_url').value = a.hostname;	  
	 }
	 else
	 {
		if (!a.href.toLowerCase().startsWith("https"))
			document.getElementById('instant_URL').value = "http://"+document.getElementById('instant_URL').value;		 	 
		a.href = document.getElementById('instant_URL').value;
		document.getElementById('instant_url').value = a.hostname;
	 }
	 if (a.port == "") 
		if (a.href.toLowerCase().startsWith("https"))
			document.getElementById('instant_port').value= "443";
		else
			document.getElementById('instant_port').value= "80";
	 else document.getElementById('instant_port').value = a.port;
	 document.getElementById('instant_path').value = a.pathname+a.search+a.hash;	 
}

function prevStation() {
	var select= document.getElementById('stationsSelect').selectedIndex ;
	if (select >0)
	{
		document.getElementById('stationsSelect').selectedIndex = select - 1;
		Select();
	}
}
function nextStation() {
	var select= document.getElementById('stationsSelect').selectedIndex ;
	if (select < document.getElementById('stationsSelect').length - 1)
	{
		document.getElementById('stationsSelect').selectedIndex = select + 1;
		Select();
	}
}
// autoplay checked or unchecked
function autoplay() {
	try{		
		xhr.open("POST","auto",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send("id=" +document.getElementById('aplay').checked+"&");		
	} catch(e){console.log("error"+e);}	
}

//ask for the state of autoplay
function autostart() {
	xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && xhr.status == 200) {	
			var arr = JSON.parse(xhr.responseText);
			if (arr["rauto"] == "1")
				document.getElementById("aplay").setAttribute("checked","");
			else
				document.getElementById("aplay").removeAttribute("checked") ;			
		}
	}
	try{		
		xhr.open("POST","rauto",false); // request auto state
		xhr.setRequestHeader(content,ctype);
		xhr.send("&");		
	} catch(e){console.log("error"+e);}	
}
//ask for the state of the theme
function atheme() {
	xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && xhr.status == 200) {	
			var arr = JSON.parse(xhr.responseText);
			themeIn = arr["theme"]  ;			
		}
	}
	try{		
		xhr.open("POST","theme",false); // request auto state
		xhr.setRequestHeader(content,ctype);
		xhr.send("&");		
	} catch(e){console.log("error"+e);}	
}

function Select() {
	if (document.getElementById('aplay').checked)
		 playStation() ;
}

function setEditBackground(tr) {
		if (themeIn == '1')
			tr.style.background =  "#1a3c56";
		else
			tr.style.background = "rgb(185, 213, 236)";
}
function playEditStation(tr) {
	if (stchanged) stChanged();
	id = tr.cells[0].innerText;
	if ((editPlaying)&&(editIndex== tr))
	{
		stopStation();
		tr.style.background = "initial";
//		editPlaying = false;
		editIndex = 0;
	}
	else{
		if (editIndex != 0) editIndex.style.background = "initial";
		wsplayStation(id); // select the station in the list
//		editPlaying = true;
		editIndex = tr;
//		getComputedStyle(element).getPropertyValue('--color-font-general');
		setEditBackground(tr);
		playStation() ; //play it 
	}
}

function playStation() {
	var select,id;
	try{
//	checkwebsocket();
		mpause();
		select = document.getElementById('stationsSelect');
		id = select.options[select.selectedIndex].value.split(":");
		id = id[0];
		localStorage.setItem('selindexstore', select.selectedIndex.toString());
		xhr = new XMLHttpRequest();
		xhr.open("POST","play",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send("id=" + id+"&");
		editPlaying = true;
	} catch(e){console.log("error"+e);}
}
function stopStation() {
	var select = document.getElementById('stationsSelect');
//	checkwebsocket();
	mstop();
	editPlaying = false;
	localStorage.setItem('selindexstore', select.options.selectedIndex.toString());
	try{
		xhr = new XMLHttpRequest();
		xhr.open("POST","stop",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send();
	} catch(e){console.log("error"+e);}
}
function saveSoundSettings() {
	xhr = new XMLHttpRequest();
	xhr.open("POST","sound",false);
	xhr.setRequestHeader(content,ctype);
	xhr.send(
	           "&bass=" + document.getElementById('bass_range').value 
			 +"&treble=" + document.getElementById('treble_range').value
	         + "&bassfreq=" + document.getElementById('bassfreq_range').value 
			 + "&treblefreq=" + document.getElementById('treblefreq_range').value
			 + "&spacial=" + document.getElementById('spacial_range').value
			 + "&");
}

function fixedEncodeURIComponent (str) {
  return str.replace(/[&]/g, function(c) {
    return '%' + c.charCodeAt(0).toString(16);
  });
}
function saveStation() {
	var file = document.getElementById('add_path').value,
		url = document.getElementById('add_url').value,jfile,jname;
		name = document.getElementById('add_name').value;
	if (!(file.substring(0, 1) === "/")) file = "/" + file;
    jfile = fixedEncodeURIComponent (file);
	jname = encodeURIComponent (name);
	console.log("Path: "+file);
	console.log("JSON: "+jfile);
	console.log("Name: "+name);
	console.log("JSON: "+jname);
//	url = url.replace(/^https?:\/\//,'');
	try{
		xhr = new XMLHttpRequest();
		xhr.open("POST","setStation",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send("nb=" + 1+"&id=" + document.getElementById('add_slot').value + "&url=" + url + "&name=" + jname + "&file=" + jfile + "&ovol=" + document.getElementById('ovol').value+"&port=" + document.getElementById('add_port').value+"&&");
		localStorage.setItem(document.getElementById('add_slot').value,"{\"Name\":\""+document.getElementById('add_name').value+"\",\"URL\":\""+url+"\",\"File\":\""+file+"\",\"Port\":\""+document.getElementById('add_port').value+"\",\"ovol\":\""+document.getElementById('ovol').value+"\"}");
	} catch(e){console.log("error save "+e);}
	abortStation(); // to erase the edit field
	loadStations();
	loadStationsList(maxStation);
}
function abortStation() {
	document.getElementById('editStationDiv').style.display = "none";
//	setMainHeight("tab-content2");
}
function eraseStation() {
	document.getElementById('editStationDiv').style.display = "block";	
			document.getElementById('add_url').value = "";
			document.getElementById('add_name').value = "";
			document.getElementById('add_path').value = "";
			document.getElementById('add_port').value = "";
			document.getElementById('ovol').value = 0;
			document.getElementById('add_URL').value = ""
}

//
function editInstantStation() {
	var arr, id = 0;		
		
	do {
		idstr = id.toString();
		try{
			arr = JSON.parse(localStorage.getItem(idstr));
		} catch(e){console.log("error"+e);}	
		id++;
	} while (arr["URL"].length >0 );
	
   id--;
	
	if (id <=254)
	{
		document.getElementById('editStationDiv').style.display = "block";		
		document.getElementById('add_slot').value = id;
		
		document.getElementById('ovol').value = '0';
		
		var str = document.getElementById('instant_URL').value;
		if (str.toLowerCase().startsWith("https"))
			document.getElementById('add_URL').value = str;
		else
			document.getElementById('add_URL').value = "http://"+document.getElementById('instant_url').value+":"+document.getElementById('instant_port').value+document.getElementById('instant_path').value;
		parseEditURL();
	} else alert("No free slot.");
}


function editStation(id) {
	var arr; 
	document.getElementById('editStationDiv').style.display = "block";	
	function cpedit(arr) {
			
			document.getElementById('add_url').value = arr["URL"];
			document.getElementById('add_name').value = arr["Name"];
			document.getElementById('add_path').value = arr["File"];
			if (arr["Port"] == "0") arr["Port"] = "";
			document.getElementById('add_port').value = arr["Port"];
			document.getElementById('ovol').value = arr["ovol"];
			
			var str = document.getElementById('add_url').value;
			if (str.toLowerCase().startsWith('https', 0))
				document.getElementById('add_URL').value = document.getElementById('add_url').value+":"+document.getElementById('add_port').value+document.getElementById('add_path').value;
			else
				document.getElementById('add_URL').value = "http://"+document.getElementById('add_url').value+":"+document.getElementById('add_port').value+document.getElementById('add_path').value;
//			setMainHeight("tab-content2");
	}
	document.getElementById('add_slot').value = id;
	idstr = id.toString();			
	if (localStorage.getItem(idstr) != null)
	{	
		
		try{
			arr = JSON.parse(localStorage.getItem(idstr));
		} catch(e){console.log("error"+e);}
		cpedit(arr);
	}
	else {
		xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4 && xhr.status == 200) {
				try{
					arr = JSON.parse(xhr.responseText);
				} catch(e){console.log("error"+e);}
				cpedit(arr);
			}
		}
		xhr.open("POST","getStation",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send("idgp=" + id+"&");
	}
}


function refreshList() {
	promptworking(working);
	intervalid =window.setTimeout(refreshListtemp, 10);
}
function refreshListtemp() {
	if (stchanged) stChanged();
	localStorage.clear();
	loadStationsList(maxStation);
	loadStations();

	promptworking("");
	refresh();
}
function clearList() {
		promptworking(working);
	if (confirm("Warning: This will clear all stations.\n Be sure to save station before.\nClear now?"))
	{
		xhr = new XMLHttpRequest();
		xhr.open("POST","clear",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send( );
		refreshList();
		window.setTimeout(loadStations, 10);
	}
	else 	promptworking("");
}	

function upgrade()
{
	try{
		xhr = new XMLHttpRequest();
		xhr.open("POST","upgrade",false);
		xhr.setRequestHeader(content,ctype);
		xhr.send();
	} catch(e){console.log("error"+e);}	
	
//	alert("Rebooting to the new release\nPlease refresh the page in few seconds.");
}
function checkhistory()
{
    if (window.XDomainRequest) {
        xhr = new XDomainRequest(); 
    } else if (window.XMLHttpRequest) {
        xhr = new XMLHttpRequest(); 
    }
	 xhr.onload = function() {
		document.getElementById('History').innerHTML = xhr.responseText;	
    }
	xhr.open("GET","http://KaraDio.karawin.fr/history132.php", false);
	try{
		xhr.send(null );
	}catch(e){;}
	setMainHeight(curtab);	
}
function checkinfos()
{
    if (window.XDomainRequest) {
        xhr = new XDomainRequest(); 
    } else if (window.XMLHttpRequest) {
        xhr = new XMLHttpRequest(); 
    }
	 xhr.onload = function() {
		document.getElementById('Infos').innerHTML = xhr.responseText;	
    }
	xhr.open("GET","http://KaraDio.karawin.fr/infos.php", false);
	try{
		xhr.send(null );
	}catch(e){;}
}
//load the version and history html
function checkversion()
{
    if (window.XDomainRequest) {
        xhr = new XDomainRequest(); 
    } else if (window.XMLHttpRequest) {
        xhr = new XMLHttpRequest(); 
    }
	 xhr.onload = function() {
		document.getElementById('Version').innerHTML = xhr.responseText;	
		document.getElementById('newrelease').innerHTML = document.getElementById('firmware_last').innerHTML;
    }
	xhr.open("GET","http://KaraDio.karawin.fr/version32.php", false);
	try{
		xhr.send(null );
	}catch(e){;}
	checkinfos();
	//checkhistory();
}

// refresh the stations list by reading a file
function downloadStations()
{
	var i,indmax,tosend,arr,reader,lines,line,file;
	if (window.File && window.FileReader && window.FileList && window.Blob) {
		reader = new FileReader();
		xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			promptworking(working); // some time to display promptworking
		}
		reader.onload = function(e){
			function fillInfo(ind,arri){
				if (!arri["ovol"]) arri["ovol"]= "0";
				tosend = tosend+"&id="+ind + "&url="+arri["URL"] +"&name="+ arri["Name"]+ "&file="+fixedEncodeURIComponent (arri["File"]) + "&port=" + arri["Port"]+"&ovol=" + arri["ovol"]+"&";
				localStorage.setItem(ind,"{\"Name\":\""+arri["Name"]+"\",\"URL\":\""+arri["URL"] +"\",\"File\":\""+arri["File"]+"\",\"Port\":\""+arri["Port"] +"\",\"ovol\":\""+arri["ovol"]  +"\"}");
			}	
			// Entire file
			//console.log(this.result);
			// By lines
			lines = this.result.split('\n');
			localStorage.clear();
			indmax = 3;
			line = 0;
			try {
				tosend =  "nb=" + indmax;
				for (i = 0 ; i< indmax;i++)
				{
					arr = JSON.parse(lines[i]);
					fillInfo(i,arr);
				}				
				xhr.open("POST","setStation",false);
				xhr.setRequestHeader(content,ctype);
//				console.log("post "+tosend);
				xhr.send(tosend);
				} catch (e){console.log("error "+e+" "+tosend);}
//			}
			indmax = 4;
			for(line = 3; line < lines.length; line+=indmax){				
//				console.log(lines[line]);
				try {
				tosend =  "nb=" + indmax;
				for (i = 0 ; (i< indmax)&&((line+i) <maxStation);i++)
				{
					if (lines[line+i] != "")
					arr = JSON.parse(lines[line+i]);
					fillInfo(line+i,arr);
				}
				if (i>0)
				{
					xhr.open("POST","setStation",false);
					xhr.setRequestHeader(content,ctype);
					xhr.send(tosend);
				}
				} catch (e){console.log("error "+e+" "+tosend);}
				
			}
			loadStationsList(maxStation);		

		};
		file = document.getElementById('fileload').files[0];
		if (file==null) alert("Please select a file");
		else {			
			promptworking(working);		
			reader.readAsText(file);			
		}
	}	
}	
function dragStart(ev) {
    ev.dataTransfer.setData("Text", ev.target.id);
}

function moveNodes(a, b){
	var pa1= a.parentNode, sib= b.nextSibling,txt;
	if(sib=== a) sib= sib.nextSibling;
	pa1.insertBefore(a, b);
	txt = 0 ; 
	for (txt=0;txt<maxStation;txt++)
	{
		pa1.rows[txt].cells[0].innerText = txt.toString();
		pa1.rows[txt].cells[3].innerHTML = b.parentNode.rows[txt].cells[3].innerHTML ;
	}
	stchanged = true;
	document.getElementById("stsave").disabled = false;
}
function dragDrop(ev) {
    ev.preventDefault();
    var TRStart = document.getElementById(ev.dataTransfer.getData("text"));
    var TRDrop = document.getElementById(ev.currentTarget.id);
    moveNodes(TRStart,TRDrop);
}
function allowDrop(ev) {
    ev.preventDefault();
}

function stChanged()
{
	var i,indmax,tosend,index,tbody = document.getElementById("stationsTable").getElementsByTagName('tbody')[0];
	function fillInfo(ind){
				var parser = document.createElement('a');

				id=tbody.rows[ind].cells[0].innerText;
				name=tbody.rows[ind].cells[1].innerText;
				furl=tbody.rows[ind].cells[2].innerText;
				if (furl.startsWith("https"))
				{
					parser.href = furl;
					url = "https://"+parser.hostname;
				}
				else
				{
					parser.href = "http://"+furl;
					url = parser.hostname;
				}

				file = parser.pathname+parser.hash+parser.search;
				port = parser.port;
				if (!port )
					if (furl.startsWith("https"))
						port = 443;
					else
						port = 80;
/*				file=tbody.rows[ind].cells[3].innerText;
				port= tbody.rows[ind].cells[4].innerText;*/
				ovol = tbody.rows[ind].cells[3].innerText;
				localStorage.setItem(id,"{\"Name\":\""+name+"\",\"URL\":\""+url +"\",\"File\":\""+file+"\",\"Port\":\""+port+"\",\"ovol\":\""+ovol+"\"}");
				tosend = tosend+"&id="+id + "&url="+ url+"&name="+ name+ "&file="+file + "&port=" +port+"&ovol=" +ovol+"&";
	}
	promptworking(working); // some time to display promptworking
	if (stchanged && confirm("The list is modified. Do you want to save the modified list?"))
	{
		xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
		}
		promptworking(working); // some time to display promptworking
		localStorage.clear();	
		indmax = 7;
		index = 0;	
		{
			try {
				tosend = "nb=" + indmax;
				for (i = 0; i<indmax; i++)
					fillInfo(index+i);
				xhr.open("POST","setStation",false);
				xhr.setRequestHeader(content,ctype);
				xhr.send(tosend);
			} catch (e){console.log("error "+e);}		
		}
		indmax = 8;
		for (index = 7; index < maxStation; index+=indmax)
		{
			try {
				tosend = "nb=" + indmax;
				for (i = 0 ; i< indmax;i++)
					fillInfo(index+i);
				xhr.open("POST","setStation",false);
				xhr.setRequestHeader(content,ctype);
				xhr.send(tosend);
			} catch (e){console.log("error "+e);}		
		}
		loadStationsList(maxStation);		
	}
	else 
	if (stchanged) 
		loadStations();
	stchanged = false;
	document.getElementById("stsave").disabled = true;
	promptworking("");
	setMainHeight(curtab);
}
//Load the Stations table
function loadStations() {
	var new_tbody = document.createElement('tbody'),
	idlist,select,
	id = 0;
	function cploadStations(id,arr) {
			tr = document.createElement('TR'),
			td = document.createElement('TD');
			tr.draggable="true";
			tr.id = "tr"+id.toString();
			tr.ondragstart=dragStart;
			tr.ondrop=dragDrop;
			tr.ondragover=allowDrop;
			td.appendChild(document.createTextNode(id ));
			td.setAttribute('onclick', 'playEditStation(this.parentNode);');
			tr.appendChild(td);
// Name
				td = document.createElement('TD');
				td.style="word-break: break-all;overflow-wrap: break-word; word-wrap: break-word;";
				td.setAttribute('onclick','playEditStation(this.parentNode);');
				if(arr["Name"].length > 116) arr["Name"] = "Error";
				td.appendChild(document.createTextNode(arr["Name"]));
				tr.appendChild(td);
// URL
				td = document.createElement('TD');
				td.style="word-break: break-all;overflow-wrap: break-word; word-wrap: break-word;";
				td.setAttribute('onclick','playEditStation(this.parentNode);');
				if (arr["Name"].length > 0)
				{
					if(arr["URL"].length > 116) arr["URL"] = "Error";
					if(arr["File"].length > 116) arr["File"] = "Error";
					if(arr["Port"].length > 116) arr["Port"] = "Error";
					td.appendChild(document.createTextNode(arr["URL"] + ":" + arr["Port"] + arr["File"]));
				} else
					td.appendChild(document.createTextNode(""));
				tr.appendChild(td);
// Ovol
				td = document.createElement('TD');
				td.style="word-break: break-all;overflow-wrap: break-word; word-wrap: break-word;";
				td.setAttribute('onclick','playEditStation(this.parentNode);');
				if(arr["ovol"].length > 116) arr["ovol"] = "Error";
				td.appendChild(document.createTextNode(arr["ovol"]));
				tr.appendChild(td);

// edit button			
			td = document.createElement('TD');
			td.style="text-align: center; vertical-align: middle;";
			td.innerHTML = "<a href=\"javascript:void(0)\" onClick=\"editStation("+id+")\">Edit</a>";
			tr.appendChild(td);
			if (idlist === idstr){
				setEditBackground(tr);
				editIndex = tr;
				editPlaying = true;
			}
			new_tbody.appendChild(tr);
	}	
	select = document.getElementById('stationsSelect');
	try{
	idlist = select.options[select.selectedIndex].value.split(":");
	idlist = idlist[0];	
	} catch(e) {idlist = 0;}
	for(id; id < maxStation; id++) {
		idstr = id.toString();		
		if (localStorage.getItem(idstr) != null)
		{	
			try{
				arr = JSON.parse(localStorage.getItem(idstr));
			} catch (e){console.log("error"+e);}			
			cploadStations(id,arr);
		}
		else
		try {
			xhr = new XMLHttpRequest();
			xhr.onreadystatechange = function() {
				if (xhr.readyState == 4 && xhr.status == 200) {
					try{
						arr = JSON.parse(xhr.responseText);
					} catch (e){console.log("error"+e);}	
					localStorage.setItem(idstr,xhr.responseText);
					cploadStations(id,arr);
				}
			}
			xhr.open("POST","getStation",false);
			xhr.setRequestHeader(content,ctype);
			xhr.send("idgp=" + id+"&");
		} catch(e){console.log("error"+e);id--;}
	}

	old_tbody = document.getElementById("stationsTable").getElementsByTagName('tbody')[0];
	old_tbody.parentNode.replaceChild(new_tbody, old_tbody);
	setMainHeight("tab-content2");
}

//Load the selection with all stations
function loadStationsList(max) {
	var foundNull = false,id,opt,arr,select, liste= [],i;
	select = document.getElementById("stationsSelect");
	//clear Select
    for(i = select.options.length - 1 ; i >= 0 ; i--)
    {
        select.remove(i);
    }
	
	function cploadStationsList(id,arr) {
		foundNull = false;
			if(arr["Name"].length > 0) 
			{
				opt = document.createElement('option');
				opt.appendChild(document.createTextNode(id+": \t"+arr["Name"]));
				select.add(opt);
			} else foundNull = true;
			return foundNull;
	}		
	select.disabled = true;
	promptworking(working);
	for(id=0; id<max; id++) {
		idstr = id.toString();
		if (localStorage.getItem(idstr) != null)
		{	
			try {
				arr = JSON.parse(localStorage.getItem(idstr));
			} catch(e){console.log("error"+e);}
			foundNull = cploadStationsList(id,arr);
		}
		else
		try {
			xhr = new XMLHttpRequest();
			xhr.onreadystatechange = function() {			
				if (xhr.readyState == 4 && xhr.status == 200) {
					try {
						arr = JSON.parse(xhr.responseText);
					} catch(e){console.log("error"+e);}
					localStorage.setItem(idstr,xhr.responseText);
					foundNull = cploadStationsList(id,arr);
				}
			}
			xhr.open("POST","getStation",false);
			xhr.setRequestHeader(content,ctype);
			xhr.send("idgp=" + id+"&");
		} catch(e){console.log("error"+e); id--;}
	}
	
	promptworking("");
	select.disabled = false;
	select.options.selectedIndex= parseInt(localStorage.getItem('selindexstore'));
}
function setMainHeight(name) {
	intervalid =window.setTimeout(setMainHeightd,10,name );	
}

function setMainHeightd(name) {
	var minh = window.innerHeight,
		h = document.getElementById(name).scrollHeight + 2* document.getElementById("HEADER").offsetHeight+50;
	if(h<minh) h = minh;
	document.getElementById("MAIN").style.height = h +"px";
	document.getElementById("MAINCONTENT").style.top = document.getElementById('HEADER').clientHeight+"px" ;
}

function resizeContent(){
	if (document.getElementById("MAINCONTENT") != null) 
	{
		setMainHeight(curtab);
	}
}
window.onresize = resizeContent;
function printList()
{
   var html="<html>";
   id = 0;
   html+="</html>";
   html+="<h1>KaraDio Stations list</h1><br/><hr><br/>";
   for(id; id < maxStation; id++) {
     idstr = id.toString();
	 if (localStorage.getItem(idstr) != null)
	 {	
		try {
				arr = JSON.parse(localStorage.getItem(idstr));
		} catch(e){console.log("error"+e);}
		if(arr["Name"].length > 0) 
		{
			html+=idstr+"&nbsp;&nbsp;"+arr["Name"]+"<br/>";
		}
	 }		
   }
   var printWin = window.open('','','left=0,top=0,width=1,height=1,toolbar=0,scrollbars=0,status  =0');
   printWin.document.write(html);
   printWin.document.close();
   printWin.focus();
   printWin.print();
   printWin.close();
}

document.addEventListener("DOMContentLoaded", function() {
	document.getElementById("tab1").addEventListener("click", function() {
			if (stchanged) stChanged();
			refresh();
			curtab = "tab-content1";
			setMainHeight(curtab);
	});
	document.getElementById("tab2").addEventListener("click", function() {
			if (stchanged) stChanged();
			loadStations(/*1*/);
			curtab = "tab-content2";
			intervalid =window.setTimeout(setMainHeight,5,curtab );			
	});
	document.getElementById("tab3").addEventListener("click", function() {
			if (stchanged) stChanged();
			curtab = "tab-content3";
			wifi(0) ;
			hardware(0);
			checkversion();
			document.getElementById('atzo').innerHTML = timezone(new Date().getTimezoneOffset()); 	
			setMainHeight(curtab);	
	});
	window.addEventListener("keydown", function (event)
	{
		if (event.defaultPrevented) {
			return; 
		}
		if (event.ctrlKey) 
		{
		switch (event.key) {
		case ' ':
		if (editPlaying) stopStation();
		else playStation();			
		break;
		case "ArrowDown":
			nextStation();
		break;
		case "ArrowLeft":
			vol=parseInt(document.getElementById('vol_range').value);
			if (vol <5) vol = 0;
			else vol = vol -5;
			onRangeVolChange(vol ,true)	 ;		
		break;
		case "ArrowUp":
			prevStation();
		break;
		case "ArrowRight":
			vol=parseInt(document.getElementById('vol_range').value);
			if (vol > 249) vol = 254;
			else vol = vol+5;
			onRangeVolChange(vol ,true)	 ;			
		break;
		default:
		return;
		}
		event.preventDefault();
		}
		if (curtab == "tab-content2")
		{
			ed = editPlaying;
			loadStations();
			editPlaying = ed;
		}
	}, true);
	
	if (intervalid != 0)  window.clearTimeout(intervalid);
	intervalid = 0;
	if (timeid != 0)  window.clearInterval(timeid);
	timeid = window.setInterval(dtime,1000);
	if (window.location.hostname != "192.168.4.1")
		loadStationsList(maxStation);
	else document.getElementById("tab3").click();
	checkwebsocket();
	promptworking("");
	refresh();
	wifi(0) ;
	hardware(0);
	autostart();
	atheme();
	checkversion(); 
	setMainHeight(curtab);
});

