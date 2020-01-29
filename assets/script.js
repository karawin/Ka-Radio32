'use strict';

/*
 * Copyright (c) Jean-Pierre Pourrez - http://github.com/bazooka07/Ka-Radio32
 *
 * git clone --depth 1 https://bazooka07@github.com/bazooka07/Ka-Radio32.git -b gh-pages
 * cd Ka-Radio32/
 * # setup IP_ADDR constant for you Ka-Radio device in index.php
 * php -S localhost:8080
 * # open the above address in your web-browser
 * # Enjoy the new homepage for your device
 * # Try a playlist in the "About" tab
 * # Search stations in shoutcast.com, radio-browser.info, Soma-Fm, Calm-Radio or Ferarock directories
 *
 * # Have a good journey in the world of web radios
 *
 * */
const KA_RADIO = 'Ka-Radio';
const meta = document.getElementById('icy-meta');
const stationsList = document.getElementById('stationsList');
const stationsSelect = document.getElementById('icy-curst');
const stationsBtn = document.getElementById('stationsBtn');
const currentVolume = document.getElementById('icy-vol');
const autoplay = document.getElementById('icy-auto');
// http://www.mediaelementjs.com/
const player = document.getElementById('monitor-audio');
const localTime = document.getElementById('localTime');
const delayTimes = {
	Sleep: document.getElementById('sleep-laptime'),
	Wake: document.getElementById('wake-laptime')
}
const rssi = document.getElementById('rssi');
const progressBar = document.getElementById('progressBar');
const contentTypeForm = 'application/x-www-form-urlencoded';
const ICY_FIELDS = new Array('curst', 'descr', 'name', 'bitr', 'url1', 'not1', 'not2', 'genre', 'meta');
const MAX_STATIONS = 255;
// const MAX_STATIONS = 20;
const MINUTES = 60000; // duration in miliseconds

var IP_DEVICE = null;
var rssiTimer = null;
var instantPlaying = false;
var saveAsText = null;
var currentStationId = null;
var isConnected = false;
var wsVersion = -1;

var isLoading = false; // displayed webradios are not saving in the Ka-Radio device if true

// https://github.com/karawin/Ka-Radio32/wiki#html-interface-for-the-wifi-webradio

function setCustomHeader(xhr, action) {
	if(typeof IP_DEVICE == 'string') {
		xhr.setRequestHeader('Karadio-Action', action);
	}
}

function sendForm(xhr1, action, params) {
	if(!isConnected) { return; }

	const url = (typeof IP_DEVICE != 'string') ? '/' + action : window.location.href;
	xhr1.open('POST', url);
	xhr1.setRequestHeader('Content-Type', contentTypeForm);
	if(typeof IP_DEVICE == 'string') {
		xhr1.setRequestHeader('Karadio-Action', action);
	}
	xhr1.send(params);
}

function pageReset() {
	ICY_FIELDS.forEach(function (field) {
		const el = document.getElementById('ici-' + field);
		if (el != null) {
			if (field.lastIndexOf('not') == 0) {
				el.innerHTML = '';
			} else {
				el.textContent = '';
				if (el == 'url1') {
					el.href = '#';
				}
			}
		}
	});
	meta.textContent = KA_RADIO;
	player.src = '';
	document.getElementById('monitor-url').innerHTML = '&nbsp;';
}

function icyDisplay(icy) {
	for (var field in icy) {
		const value = (typeof icy[field] == 'string') ? icy[field].trim() : icy[field];
		if(['bass', 'treb', 'bfreq', 'tfreq', 'spac'].indexOf(field) < 0) {
			const target = document.getElementById('icy-' + field);
			if (target != null) {
				switch (field) {
					case 'auto':
						target.checked = (value == 1);
						break;
					case 'curst':
					case 'vol':
						target.value = value;
						if (field == 'curst') {
							currentStationId = value;
						}
						break;
					case 'not1':
					case 'not2':
					case 'descr':
						target.innerHTML = value.replace(/<br\s*\/?>/i, '');
						break;
					case 'bitr':
						target.textContent = (value.length > 0 && value > 0) ? value + ' kB/s' : '';
						break;
					case 'url1':
						if(value.length > 0) {
							target.href = ((/^https?:\/\//.test(value.trim())) ? '' : 'http://') + value;
							target.textContent = target.href;
						} else {
							target.href = '#';
							target.textContent = '';
						}
						break;
					default:
						target.textContent = value;
				}
			} else {
				console.error('icy-' + field + ' element not found');
			}
		} else {
			if(field != 'spac') {
				const el = document.getElementById('icy-' + field);
				el.value = value;
				let content = '';
				switch(field) {
					case 'bfreq':
						content = value + '0 Hz';
						break;
					case 'tfreq':
						content = value + ' KHz';
						break;
					default:
						content = value + ' dB';
				}
				el.nextElementSibling.innerHTML = content;
			} else {
				document.forms.hardware.elements.spacial.value = value;
			}
		}
	}
	if('name' in icy) {
		const playing = (icy.name.trim().length > 0);
		stationsBtn.playing = playing;
		stationsBtn.textContent = (playing) ? 'Stop' : 'Play';
	}
}

document.getElementById('logo').addEventListener('click', function (event) {
	event.preventDefault();
	document.body.classList.toggle('dark');
});

function valueChange(event) {
	event.preventDefault();
	if (!'action' in this.dataset || !'param' in this.dataset) {
		console.log('Missing data-action or data-param attribute for :', this);
		return;
	}
	var value = this.value;
	switch (this.dataset.action) {
		case 'play':
			pageReset();
			instantPlayForm.classList.remove('active');
			if(isConnected) {
				if(!isLoading) {
					// xhr.valueChange(this.dataset.action, this.dataset.param + '=' + value + '&'); // Hack against Ka-Radio
					xhr.sendCommand('play', value);
				} else {
					// stations in the playlist table and select are from a file, not from the Ka-Radio device
					const row = document.getElementById('station-' + value) ;
					if(row != null) {
						instantPlayForm.elements.fullUrl.value = row.cells[2].textContent;
						instantPlayForm.elements.instantPlayBtn.click();
					}
				}
			} else {
					const row = document.getElementById('station-' + value) ;
					if(row != null) {
						player.src = row.cells[2].textContent;
						player.play();
					}
			}
			return;
			break;
		case 'soundvol':
		case 'volume':
			xhr.sendCommand('volume', value);
			return;
			break;
		case 'auto':
			value = (this.checked) ? 'true' : 'false';
			break;
	}
	xhr.valueChange(this.dataset.action, this.dataset.param + '=' + value);
}

stationsSelect.addEventListener('change', valueChange);
currentVolume.addEventListener('change', valueChange);
autoplay.addEventListener('change', valueChange);

/* =========== Instant play ================= */

const instantPlayForm = document.forms.instantPlayForm;
const instantPlaySaveBtn = document.getElementById('instantPlaySaveBtn');

function extractFullUrl(fullUrl) {
	const matches = /(?:https?:\/\/)([^:/]*)(?::(\d{2,5}))?(\/.*)?$/.exec(fullUrl);
	if(matches == null) {
		return false;
	}

	return {
		url: matches[1],
		port: (typeof matches[2] === 'string') ? matches[2] : '80',
		path1: (typeof matches[3] === 'string') ? matches[3] : '/'
	}
}

function onInstantPlay(event) {
	event.preventDefault();
	const fullUrl = this.elements.fullUrl.value.trim();
	instantPlaySaveBtn.disabled = (fullUrl.length <= 0);
	if (fullUrl.length == 0) {
		alert('Url is empty');
		return;
	}
	console.log('Instant play', fullUrl);

	pageReset();
	xhr.instantPlay(fullUrl);
	this.classList.add('active');
	return false;
}

function instantPlaySave(event) {
	const editStation = document.forms.editStationForm;
	editStation.elements.idStation.value = '';
	editStation.elements.nameStation.value = document.getElementById('icy-name').textContent.trim();
	editStation.elements.urlStation.value = player.src;
	editStation.elements.volStation.value = '0';
	document.getElementById('aside').classList.add('active');
}

function playStation() {
	const event = new Event('change');
	stationsSelect.dispatchEvent(event);
}

if (instantPlayForm != null) {
	instantPlayForm.addEventListener('submit', onInstantPlay);
	instantPlayForm.elements.fullUrl.addEventListener('change', function (event) {
		let noURL = (instantPlayForm.elements.fullUrl.value.trim().length == 0);
		instantPlaySaveBtn.disabled = noURL;
		// instantPlayForm.elements.instantPlayBtn.disabled = noURL;
	});
	instantPlaySaveBtn.addEventListener('click', instantPlaySave);
}

/* =========== webSocket ================ */

var kaRadioInstantPlay = {
	url: '',
	port: '',
	path: ''
}

var websocket = null;

function setRssiInterval() {
	setInterval(function () {
		try {
			if (websocket == null || websocket.readyState == WebSocket.CLOSED) {
				openSocket();
			} else {
				websocket.send('wsrssi');
			}
		} catch (e) {
			console.error('Websocket ', e);
			clearInterval(rssiTimer);
			rssiTimer = null;
		}
	}, 5000);
}

/*
 * Commands for the websocket ( void websockethandle(...) in webserver.c )
 * wsvol=, startSleep=, stopSleep, startWake=, stopWake, monitor, theme, wsrssi
 * values en minutes for start(Sleep|Wake)=
 * */
function openSocket() {
	const url = (typeof IP_DEVICE == 'string') ? IP_DEVICE : window.location.hostname;
	websocket = new WebSocket('ws://' + url);
	if (websocket != null) {
		websocket.onopen = function (event) {
			console.log(this.url + ' opened');
			if(wsVersion > 0) {
				loadStationsList();
			}
		}

		websocket.onmessage = function (event) {
			try {
				// console.log('msg', event.data);
				let msg = JSON.parse(event.data);
				if('station' in msg && 'URL' in msg) {
					if(msg.URL.trim().length > 0) {
						addStation(msg.station, msg);
					}
					const i = msg.station + 1;
					progressBar.value = i;
					if(i<MAX_STATIONS) {
						this.send('getStation=' + i);
					} else {
						stationsBtn.disabled = false;
					}
					return;
				}
				if('stations' in msg && typeof msg.stations.forEach != 'undefined') {
					if(msg.stations.length > 0) {
						let i = 0;
						msg.stations.forEach(function(item) {
							console.log(item);
							addStation(item.station, item);
							progressBar.value = i;
							if(i<item.station) {
								i = item.station;
							}
						});
						i++;
						if(i<MAX_STATIONS) {
							if(wsVersion >= 2) {
								this.send('getStationsFrom=' + i);
							} else {
								this.send('getStation=' + i);
							}
						} else {
							stationsBtn.disabled = false;
						}
					} else {
						progressBar.value = MAX_STATIONS;
					}
					return;
				}
				if(!'wsrssi' in msg) {
					console.log('websocket:', msg);
				}

				if ('meta' in msg) {
					let value = (msg.meta.length > 0) ? msg.meta : KA_RADIO;
					meta.textContent = value;
					return;
				}

				if ('wsvol' in msg) {
					currentVolume.value = msg.wsvol;
					return
				}

				if ('wsicy' in msg) {
					icyDisplay(msg.wsicy);
					return;
				}

				if ('wssound' in msg) {
					return
				}

				if ('monitor' in msg) {
					if (player != null) {
						player.src = msg.monitor;
						// displayCurrentStation(); // Post /play may give an empty answer
					}
					let caption = document.getElementById('monitor-url');
					if (caption != null) {
						caption.textContent = msg.monitor;
					}
					return;
				}

				if ('wsstation' in msg) {
					stationsSelect.value = msg.wsstation;
					return;
				}

				if ('wsrssi' in msg) {
					rssi.textContent = msg.wsrssi + ' dBm';
					return
				}

				if ('iurl' in msg) {
					kaRadioInstantPlay.url = msg.iurl;
					kaRadioInstantPlay.port = '80';
					kaRadioInstantPlay.path = '/';
					return
				}

				if ('iport' in msg) {
					kaRadioInstantPlay.port = msg.iport;
					return
				}

				if ('ipath' in msg) {
					kaRadioInstantPlay.path = msg.ipath;
					instantPlayForm.elements.fullUrl.value = 'http://' + kaRadioInstantPlay.url + ':' + kaRadioInstantPlay.port + kaRadioInstantPlay.path;
					return
				}

				if ('upgrade' in msg) {
					return
				}
			} catch (err) {
				console.error('Error on message: ', err);
			}
		}

		websocket.onclose = function (event) {
			console.log(this.url + ' closed');
		}

		websocket.onerror = function (event) {
			console.error('Websocker error: ', event.originalTarget);
			this.close();
		}

		if (websocket.readyState == WebSocket.OPEN) {
			websocket.send('opencheck');
		}
	}

	if (rssiTimer != null) {
		clearInterval(rssiTimer);
		displayCurrentStation();
	}
}

const localTimeTimer = setInterval(function () {
	let now = new Date();
	localTime.textContent = now.toLocaleTimeString();
	for(let i in delayTimes) {
		if(delayTimes[i] != null) {
			const k = 'user' + i;
			if(localTime.hasOwnProperty(k)) {
				const delay = localTime[k] - now.getTime();
				delayTimes[i].innerHTML = (delay <= 0) ? '&nbsp;' : 'in ' + new Date(delay).toISOString().substr(11, 8);
			}
		}
	}
}, 1000);

/* ================ Stations list =========== */

// For sorting the stationsList by Drag & Drop
var dragSrcEl = null;

function onDragstart(event) {
	dragSrcEl = this;
	dragSrcEl.classList.add('dragElem');
	event.dataTransfer.effectAllowed = 'move';
	event.dataTransfer.setData('text/html', dragSrcEl.outerHTML);
}

function onDragend(event) {
	this.classList.remove('over');
	if (dragSrcEl != null) {
		dragSrcEl.classList.remove('dragElem');
		dragSrcEl = null;
	}
}

function onDragenter(event) {
}

function onDragover(event) {
	if (event.preventDefault) {
		event.preventDefault(); // Necessary. Allows us to drop.
	}
	this.classList.add('over');
	event.dataTransfer.dropEffect = 'move'; // See the section on the DataTransfer object.
	return false;
}

function onDragleave(event) {
	this.classList.remove('over');
}

function onDrop(event) {
	if (event.stopPropagation) {
		event.stopPropagation(); // Stops some browsers from redirecting.
	}

	// Don't do anything if dropping the same row we're dragging.
	if (dragSrcEl != this) {
		this.parentNode.removeChild(dragSrcEl);
		this.parentNode.insertBefore(dragSrcEl, this);
	}
	this.classList.remove('over');
	for (let i = 0, iMax = stationsList.rows.length - 1; i <= iMax; i++) {
		const id = 'station-' + i;
		if (stationsList.rows[i].id != id) {
			stationsList.rows[i].id = id;
			stationsList.rows[i].cells[0].textContent = i;
			stationsList.rows[i].classList.add('has-changed');
		}
	}
}

function setDrapAndDrop(row) {
	row.draggable = true;
	row.addEventListener('dragstart', onDragstart);
	row.addEventListener('dragend', onDragend);
	row.addEventListener('dragenter', onDragenter);
	row.addEventListener('dragover', onDragover);
	row.addEventListener('dragleave', onDragleave);
	row.addEventListener('drop', onDrop);
}

/* Add station in the table and select tags */
function addStation(stationId, datas) {
	// datas : { Name: '', URL: '', Port: '', File: '', ovol: '' }
	let newStation = (stationId == null || stationId.length === 0);
	if (newStation) {
		let rows = stationsList.rows;
		stationId = -1;
		// searches the max value for stationId
		for (let i = 0, iMax = rows.length; i < iMax; i++) {
			if (rows[i].id.startsWith('station-')) {
				let id = parseInt(rows[i].id.substr(8));
				if (stationId < id) {
					stationId = id;
				}
			}
		}
		stationId++;
	}

	if(!datas.hasOwnProperty('fullUrl') && datas.URL.length > 0) {
		let port = '';
		if(datas.hasOwnProperty('Port')) {
			if(typeof datas.Port == 'string') {
				if(datas.Port.trim() != '80') {
					port = ':' + datas.Port.trim();
				}
			} else if(datas.Port != 0 && datas.Port != 80) {
				port = ':' + datas.Port;
			}
		}
		datas.fullUrl = datas.URL + port + datas.File;
	/*
	} else {
		datas.fullUrl = '';
	 * */
	}

	let tr = document.createElement('TR');
	tr.id = 'station-' + stationId;
	tr.draggable = true;
	if(isLoading) {
		tr.classList.add('has-changed');;
	} else {
		tr.classList.remove('has-changed');;
	}

	let idCell = document.createElement('TD');
	idCell.textContent = stationId;
	tr.appendChild(idCell);

	let nameCell = document.createElement('TD');
	if (datas.Name.trim().length > 0) {
		nameCell.textContent = datas.Name;
		/* select */
		let option = document.createElement('OPTION');
		option.textContent = stationId + ': ' + datas.Name;
		option.value = stationId;
		if(stationId == currentStationId) { option.selected = true; }
		stationsSelect.appendChild(option);
		if (currentStationId == stationId && stationsSelect.value == '') {
			stationsSelect.value = currentStationId;
		}
	} else {
		nameCell.innerHTML = '&nbsp;';
	}
	tr.appendChild(nameCell);
	let urlCell = document.createElement('TD');
	let volCell = document.createElement('TD');

	urlCell.textContent = (datas.fullUrl.length == 0 ) ? '' : ((/^https?:\/\//.test(datas.fullUrl)) ? '' : 'http://') + datas.fullUrl;
	volCell.textContent = (datas.hasOwnProperty('ovol')) ? datas.ovol : '0';
	tr.appendChild(urlCell);
	tr.appendChild(volCell);
	stationsList.appendChild(tr);
	setDrapAndDrop(tr);
	if(isLoading) {
		console.log(datas);
	}
	return stationId;
}

/* ----------- display current station ---------------- */
const xhrCurst = new XMLHttpRequest();
xhrCurst.onreadystatechange = function () {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			// console.log(this.responseText);
			if(this.responseText.trim().length === 0 || this.getResponseHeader('Content-Type') != 'application/json') { return; }

			let datas = JSON.parse(this.responseText);
			// console.log(datas);
			if('curst' in datas) {
				icyDisplay(datas);
				meta.textContent = datas.meta;
				return;
			}

			console.error(this.status, this.statusText);
		} else {
			console.error(this.status + ': ' + this.statusText + ' from ' + this.responseURL);
		}
	}
}

function displayCurrentStation() {
	if(isConnected) {
		sendForm(xhrCurst, 'icy', null);
	}
}

/* ------------------- hardware ---------------------- */
const xhrHardware = new XMLHttpRequest();

xhrHardware.onreadystatechange = function () {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			// console.log(this.responseText);
			if (this.responseText.trim().length === 0 || !this.getResponseHeader('Content-Type').startsWith('application/json')) { return; }

			let datas = JSON.parse(this.responseText);

			if ('coutput' in datas) {
				document.forms.hardware.output.value = datas.coutput;
				return;
			}

			console.log('Error: %d (%s)', this.status, this.statusText);
		} else {
			console.log('Error ' + this.status + ': ' + this.statusText + ' from ' + this.responseURL);
		}
	}
}

function displayHardware(valid) {
	if (typeof valid == 'undefined') { valid = '0'; }
	if(valid != '0' && valid != '1') { return; }
	let params = [
		'valid=' + valid
	];
	if(valid == '1') {
		// Update the output hardware
		let device = document.forms.hardware.output.value;
		params.push('coutput=' + device);
		if(device == '4') {
			// VS1053
			alert('VS1053');
		}
	}

	sendForm(xhrHardware, 'hardware', params.join('&'));
}

const xhr = new XMLHttpRequest();
// xhr.stationId = 0;
xhr.sendForm = function(action, params) {
	const url = (typeof IP_DEVICE != 'string') ? '/' + action : window.location.href;
	this.open('POST', url);
	this.setRequestHeader('Content-Type', contentTypeForm);
	setCustomHeader(this, action);
	this.send(params);
}
xhr.sendCommand = function(action, params) {
	if(typeof action == 'undefined') { return; }
	let url = '/?' + action;
	if(typeof IP_DEVICE == 'string') {
		url = window.location.href + '?' + action;
	}
	if(typeof params != 'undefined') {
		url += '=' + params;
	}
	this.open('GET', url);
	this.send();
}
xhr.saveStation = function (stationId, datas) {
	let params = 'id=' + stationId + '&name=' + encodeURI(datas.Name) + '&url=' + datas.URL + '&port=' + datas.port + '&file=' + encodeURI(datas.file) + '&ovol=' + datas.ovol;
	this.sendForm('setStation', params);
	console.log('SetStation => ', params);
}
xhr.startCurrentStation = function () {
	console.log('Start Ka-Radio');
	this.sendCommand('start');
}
xhr.stopCurrentStation = function () {
	console.log('Stop Ka-Radio');
	this.sendCommand('stop');
}
xhr.instantPlay = function (fullUrl) {
	if(isConnected) {
		// this.sendCommand('instant', encodeURI(fullUrl.replace(/^https/, 'http')));
		const matches = fullUrl.match(/^https?:\/\/([^:/]+)(?::(\d+))?(.*)/);
		if(matches != null) {
			if(typeof matches[2] == 'undefined') {
				matches[2] = '80';
			}
			if(!matches[3].startsWith('/')) {
				matches[3] = '/' + matches[3];
			}
				xhr.sendForm('instant_play', 'url=' + matches[1] + '&port=' + matches[2] + '&path=' + encodeURI(matches[3]));
		}
	} else {
		player.src = fullUrl;
		player.play();
	}
}
xhr.valueChange = function (action, params) {
	this.sendForm(action, params);
}
xhr.wifi = function (valid) {
	if (typeof valid == 'undefined') { valid = '0'; }
	const params = ['valid=' + valid];
	if(valid > 0) {
		const elements = document.forms.wifi.elements;
		['', '2'].forEach(function(col) {
			let dhcp = false;
			['ssid', 'pasw', 'dhcp', 'ip', 'msk', 'gw', 'ua', 'host', 'tzo'].forEach(function(field) {
				if(col == '2' && ['ua', 'host', 'tzo'].indexOf(field) >= 0) { return; }
				if(dhcp && ['ip', 'msk', 'gw'].indexOf(field) >= 0) { return; }
				const el = elements.namedItem(field + col);
				if(field == 'dhcp') {
					dhcp = el.checked; // type="checkbox"
					const value = (dhcp) ? 'true' : 'false'; // Hack against Ka-Radio
					params.push('dhcp' + col + '=' + value);
				} else {
					params.push(el.name + '=' + el.value);
				}
			});
		});
	}

	console.log(params);
	this.sendForm('wifi', params.join('&'));
}
xhr.hardware = function (valid) {
	if (typeof valid == 'undefined') {
		valid = '0';
	}
	if(valid != '0' && valid != '1') { return; }
	let params = [
		'valid=' + valid
	];
	if(valid == '1') {
		// Update the output hardware
		let device = document.forms.hardware.output.value;
		params.push('coutput=' + device);
	}
	this.sendForm('hardware', params.join('&'));
}
xhr.setVS1053 = function(input) {
	if(document.forms.hardware.output.value != 4) { return; }

	let params = new Array();
	const controls = ['bass', 'bassfreq', 'treble', 'treblefreq', 'spacial'];
	if(typeof input != undefined) {
		if(controls.indexOf(input.name) < 0) {
			alert('Not a valid control');
			return;
		}
		params.push(input.name + '=' + input.value);
		// alert('input for vs1053 :\n' + input.name + ' control : ' + event.target.value);
	} else {
		elements = document.forms.namedItem('hardware').elements;
		controls.forEach(function(item) {
			params.push(item + '=' + elements[item].value);
		});
	}
	this.sendForm('sound', params.join('&'));
}
xhr.getVersion = function() {
	let url = (typeof IP_DEVICE != 'string') ? '/' : window.location.href;
	this.open('GET', url + '?version');
	this.send();
}
xhr.onreadystatechange = function () {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			// console.log(this.responseText);
			if (this.responseText.trim().length === 0) {
				return;
			}

			if(this.getResponseHeader('Content-Type').startsWith('text/plain')) {
				const PATTERN = /^release\b.*?(\d+)\.(\d+).*?(\d+)(.*)/i;
				if(PATTERN.test(this.responseText)) {
					console.log('Version inside the ESP32 : ', this.responseText); // = version. Don't comment !!!
					const el = document.getElementById('version');
					el.textContent = this.responseText.trim().replace(PATTERN, 'Ver. $1.$2.$3');

					// Let's go
					isConnected = true;
					openSocket();
					displayCurrentStation();
					displayHardware();
					setRssiInterval();
					const suffixe = this.responseText.trim().replace(PATTERN, '$4');
					if(suffixe.length == 0) {
						wsVersion = -1;
						loadStationsList();
					} else {
						// use websocket for downloading the playlist quickly
						wsVersion = suffixe.replace(/.*\b(\d+)\b.*/, '$1');
					}
					return;
				}
				console.error('Unattented response from '+ this.responseURL, this.responseText);
				return;
			}

			if(this.getResponseHeader('Content-Type') != 'application/json') { return; }

			let datas = JSON.parse(this.responseText);
			// console.log(datas);
			if ('curst' in datas) {
				icyDisplay(datas);
				meta.textContent = datas.meta;
				return;
			}

			// for VS1053
			if ('treb' in datas) {
				icyDisplay(datas);
				return;
			}

			if ('URL' in datas) {
				/* loads each station in the table and the select's options */
				if (datas.URL.length > 0) {
					addStation(this.stationId, datas);
				}
				if (this.stationId < MAX_STATIONS) {
					this.stationId++;
					if (this.stationId < MAX_STATIONS) {
						this.loadStation();
					} else {
						progressBar.value = MAX_STATIONS;
						stationsBtn.disabled = false;
						if (document.getElementById('tab-settings').checked) {
							this.wifi();
						}
					}
				}
				return;
			}

			if ('ssid' in datas) {
				for (let i in datas) {
					if (i in document.forms.wifi.elements) {
						if (document.forms.wifi.elements[i].type == 'checkbox') {
							document.forms.wifi.elements[i].checked = (datas[i] == '1');
						} else {
							document.forms.wifi.elements[i].value = datas[i];
						}
					} else {
						let el = document.getElementById(i);
						if (el != null) {
							el.textContent = datas[i];
						} else {
							console.log('#' + i + ' element not found');
						}
					}
				}
				return;
			}

			if ('coutput' in datas) {
				document.forms.hardware.output.value = datas.coutput;
				return;
			}
		} else {
			console.log('Error ' + this.status + ': ' + this.statusText + ' from ' + this.responseURL);
			if(Math.round(this.status / 10) == 40 && this.responseURL.endsWith('/?version')) {
				// Error 400..409
				alert('Your device is unreachable');
				/*
				// Don't work because CORS policy
				// https://stackoverflow.com/questions/4911062/pulling-track-info-from-an-audio-stream-using-php/4914538#4914538
				player.addEventListener('loadeddata', function(event) {
					console.log(event);
					xhrIcy.open('GET', event.target.currentSrc);
					xhrIcy.setRequestHeader('Icy-MetaData', '1');
					xhrIcy.send();
				});
				 * */
			}
		}
	}
}

/* -------- download all the stations from the Ka-Radio device --------- */
const xhrSta = new XMLHttpRequest();
xhrSta.forceReload = false; // Reload the playlist after a /clear command

xhrSta.loadStation = function (stationId) {
	if (typeof stationId === 'number') {
		this.stationId = stationId;
	};
	progressBar.value = this.stationId;
	sendForm(this, 'getStation', 'idgp=' + this.stationId);
}

xhrSta.clear = function() {
	this.forceReload = true;
	sendForm(this, 'clear', null);
}

xhrSta.onreadystatechange = function () {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			// console.log(this.responseText);
			if(
				this.responseText.trim().length === 0 &&
				this.getResponseHeader('Content-Type').startsWith('text/plain') &&
				this.forceReload
			) {
				// StationsList is just cleaned up with /clear command
				this.forceReload = false;
				loadStationsList();
				return;
			}

			if(
				this.responseText.trim().length === 0 ||
				!this.getResponseHeader('Content-Type').startsWith('application/json')
			) { return; }

			try {
				let datas = JSON.parse(this.responseText);
				// console.log(datas);
				if ('URL' in datas && datas.URL.length > 0) {
					/* loads each station in the table and the select's options */
					addStation(this.stationId, datas);
				}
			} catch (error) {
				console.error(error, this.responseText);
			}
			if (this.stationId < MAX_STATIONS) {
				this.stationId++;
				if (this.stationId < MAX_STATIONS) {
					this.loadStation();
				} else {
					progressBar.value = MAX_STATIONS;
					stationsBtn.disabled = false;
					isLoading = false;
				}
			}
			return;
		}
		console.error(this.status, this.statusText + ' from ' + this.responseURL);
	}
}

const promptMsg = 'Do you want to save the entries of the playlist into the device ?\nThat takes à while. Let\'s be patient !!';

function loadStationsList() {
	if (stationsList == null) { return; }

	stationsList.innerHTML = '';
	stationsSelect.innerHTML = '';
	progressBar.max = MAX_STATIONS;
	switch(wsVersion) {
		case '1' :
			websocket.send('getStation=0');
			break;
		case '2' :
			websocket.send('getStationsFrom=0');
			break;
		default:
			xhrSta.loadStation(0);
	}
}

function reloadStationsList() {
	if(isConnected && stationsList.rows.length > 0) {
		if(isLoading) {
			if(confirm(promptMsg)) {
				saveStationsList();
			} else {
				isLoading = false;
				loadStationsList();
			}
		} else {
			saveStationsList(true); // Only changed  stations
		}
	}
}

function saveStationsList(changedOnly) {
	if(typeof changedOnly == 'undefined') {
		changedOnly = false;
	}

	const BATCH_SIZE = 8;
	let saveStationsTimer = null;

	const xhrPlaylistSave = new XMLHttpRequest();
	xhrPlaylistSave.currentRow = 0;
	xhrPlaylistSave.clear = function() {
		// Clear each station in the device before saving the all playlist
		sendForm(this, 'clear', null);
	};

	xhrPlaylistSave.saveStation = function() {
		if(saveStationsTimer != null) {
			clearTimeout(saveStationsTimer);
			saveStationsTimer = null;
		}

		const iMax=stationsList.rows.length;
		for(let i=this.currentRow; i<iMax; i++) {
			if(stationsList.rows[i].classList.contains('has-changed')) {
				this.currentRow = i;
				const output = new Array();
				for(let i=0; i<BATCH_SIZE; i++) {
					if(this.currentRow >= stationsList.rows.length) { break; }

					const row = stationsList.rows[this.currentRow];
					this.currentRow++;

					if(changedOnly && !row.classList.contains('has-changed')) { break; }
					row.classList.remove('has-changed');

					const url = row.cells[2].textContent.replace('&nbsp;', ' ').trim();
					if(url.length == 0) { break; }

					let datas = extractFullUrl(url);
					if(typeof datas == 'object') {
						output.push('id=' + row.id.replace(/.*-(\d+)$/, '$1') + '&name=' + encodeURI(row.cells[1].textContent.trim()) + '&url=' + datas.url + '&port=' + datas.port + '&file=' + encodeURI(datas.path1) + '&ovol=' + parseInt(row.cells[3].textContent.trim()) + '&');
					}

				}

				if(output.length > 0) {
					const action = 'setStation';
					let params = null;
					if(output.length != 1) {
						params = 'nb=' + output.length + '&' + output.join('&');
					} else {
						params = output[0].replace(/&+$/, '');
					}
					sendForm(this, action, params);
					console.log(action, '=>', params);
					// xhrPlaylistSave.saveStation() called again by xhrPlaylistSave.onreadystatechange()
					return;
				}
			}
		}

		isLoading = false;
		console.log('saveStationsList() is done');
		loadStationsList();
	};

	xhrPlaylistSave.onreadystatechange = function () {
		if (this.readyState === XMLHttpRequest.DONE) {
			if (this.status === 200) {
				if(this.responseText.length > 0) {
					console.log(this.responseText);
				}

				saveStationsTimer = setTimeout(function(xhr) {
					xhr.saveStation();
				}, 250, this);
				return;
			}
			console.error(this.status + ': ' + this.statusText + ' from ' + this.responseURL);
		}
	}

	// Push stations with empty url at the end of the list
	let j = -1;
	let id = 0;
	const buf = new Array();
	for(let i=stationsList.rows.length - 2; i>=0; i--) {
		const row = stationsList.rows[i];
		const url = row.cells[2].textContent.trim();
		if(url.length == 0) {
			buf.push(row);
			stationsList.removeChild(row);
			j = i;
			id = parseInt(row.id.replace(/.*-(\d+)/, '$1'));
		}
	}
	if(buf.length > 0) {
		for(let i=0, iMax = buf.length; i<iMax; i++) {
			stationsList.appendChild(buf[i]);
		}
	}

	if(changedOnly) {
		if(j>=0) {
			for(let i=j, iMax=stationsList.rows.length; i<iMax; i++) {
				stationsList.rows[i].classList.add('has-changed');
				stationsList.rows[i].cells[0].textContent = id;
				stationsList.rows[i].id = 'station-' + id;
				id++;
			}
		}
		xhrPlaylistSave.saveStation();
	} else {
		for(let i=0, iMax=stationsList.rows.length; i<iMax; i++) {
			const row = stationsList.rows[i];
			const url = row.cells[2].textContent.replace('&nbsp;', ' ').trim();
			if(url.length > 0) {
				row.classList.add('has-changed');
			}
		}
		xhrPlaylistSave.clear(); // Save all stations
	}
}

function onStationsBtnClick(event) {
	event.preventDefault();
	if (stationsBtn.playing) {
		xhr.stopCurrentStation();
		stationsBtn.textContent = 'Start';
		stationsBtn.playing = false;
	} else {
		xhr.startCurrentStation();
		stationsBtn.textContent = 'Stop';
		stationsBtn.playing = true;
	}
}

stationsBtn.addEventListener('click', onStationsBtnClick)

/* edit station */

document.getElementById('abortEditStationBtn').addEventListener('click', function (event) {
	document.getElementById('aside').classList.remove('active');
	document.forms.editStationForm.reset();
});

function saveStation(event) {
	event.preventDefault();
	let idStation = this.elements.idStation.value.trim();
	let newStation = (idStation.length == 0);
	if (!newStation) {
		// update station
		let row = stationsList.querySelector('#station-' + idStation);
		if (row != null) {
			row.cells[1].textContent = this.elements.nameStation.value;
			row.cells[2].textContent = this.elements.urlStation.value;
			row.cells[3].textContent = this.elements.volStation.value;
			row.classList.remove('has-changed');
			stationsSelect.querySelector('option[value="' + idStation + '"]').textContent = this.elements.nameStation.value;
		}
	} else {
		// new station
		idStation = addStation('', {
			Name: this.elements.nameStation.value,
			URL: this.elements.urlStation.value,
			Port: '',
			File: '',
			ovol: this.elements.volStation.value
		});
	}
	document.getElementById('aside').classList.remove('active');
	// send station to Ka-Radio
	const params = {
			Name: this.elements.nameStation.value,
			URL: '',
			port: '',
			// file: encodeURI(datas.path1),
			file: '',
			ovol: '0'
		}
	let datas = extractFullUrl(this.elements.urlStation.value);
	if(typeof datas == 'object') {
		params.URL = datas.url;
		params.port = datas.port;
		// params.file = encodeURI(datas.path1);
		params.file = datas.path1;
	}
	xhr.saveStation(idStation, params);

	if (newStation) {
		instantPlayForm.elements.fullUrl.value = '';
		instantPlayForm.classList.remove('active');
		stationsSelect.value = idStation;
	}
	return false;
}

document.forms.editStationForm.addEventListener('submit', saveStation);

document.getElementById('newStationBtn').addEventListener('click', function (event) {
	let editStation = document.forms.editStationForm;
	editStation.elements.idStation.value = '';
	editStation.elements.nameStation.value = '';
	editStation.elements.urlStation.value = '';
	editStation.elements.volStation.value = '0';
	document.getElementById('aside').classList.add('active');
});

stationsList.addEventListener('click', function (event) {
	if (event.target.tagName == 'TD' && event.target.parentElement.id.startsWith('station-')) {
		event.preventDefault();
		let row = event.target.parentElement;
		let stationId = row.id.replace(/^station-/, '');
		if (event.target.cellIndex == 2) {
			// Click on the url for editing
			let editStation = document.forms.editStationForm;
			editStation.elements.idStation.value = stationId;
			editStation.elements.nameStation.value = row.cells[1].textContent.trim();
			editStation.elements.urlStation.value = row.cells[2].textContent.trim();
			editStation.elements.volStation.value = parseInt(row.cells[3].textContent);
			document.getElementById('aside').classList.add('active');
		} else {
			// Click on the name for playing
			stationsSelect.value = stationId;
			playStation();
		}
	}
});

function savePlaylistAsM3u() {
	let downloadLink = document.getElementById('download-link');
	if (downloadLink == null) {
		console.log('#download-link element not found');
		return;
	}
	let stations = [
		'#EXTM3U',
		''
	];
	for (let i = 0, iMax = stationsList.rows.length; i < iMax; i++) {
		let cells = stationsList.rows[i].cells;
		stations.push('#EXTINF:-1,' + cells[1].textContent);
		stations.push(cells[2].textContent);
	}
	saveAsText = new Blob([stations.join('\r\n')], {
		type: 'audio/x-mpequrl'
	});
	let el = ('URL' in window) ? window.URL : window.webkitURL;
	downloadLink.href = el.createObjectURL(saveAsText);
	downloadLink.click();
	el.revokeObjectURL(saveAsText);
}

function parsePlaylist(contentType, datas, uri) {
	// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/matchAll
	let matches = null;
	let count = 0;
	switch(contentType) {
		case 'audio/x-mpegurl' :
			if(!/^#EXTM3U\b/.test(datas)) {
				console.log('Bad syntax. Missing #EXTM3U at the beginning of file');
				return;
			}

			stationsList.innerHTML = '';
			stationsSelect.innerHTML = '';
			isLoading = true;
			const pattern = RegExp('#EXTINF:-?\\d+,(.*)(?:\\r\\n|\\n|\\r)(.*)', 'g');
			matches = datas.matchAll(pattern);
			for(let item of matches) {
				// console.log(item[1], ' => ', item[2]);
				let idStation = addStation(null, {
					Name: item[1].trim(),
					fullUrl: item[2].trim()
				});
				count++;
			}
			break;
		case 'audio/x-scpls':
			if(!/^\[playlist\]/.test(datas)) {
				console.log('Bad syntax. Missing [playlist] at the beginning of file');
				return;
			}

			const plsPattern = RegExp('(File|Title)(\\d+)=(.*)', 'g');
			matches = datas.matchAll(plsPattern);
			if(matches == null) {
				return;
			}
			const entries = {};
			for(let item of matches) {
				const i = item[2];
				if(!entries.hasOwnProperty(i)) {
					entries[i] = { Name: '' };
				}
				switch(item[1]) {
					case 'File':
						if(!/^https?:\/\//.test(item[3])) {
							continue;
						}
						let value = item[3].trim().replace(/^https:/, 'http:'); // No https for Ka-Radio
						if(/^https?:\/\/[^:\/]+(:\d+)?$/.test(value)) {
							// Missing path
							value += '/';
						}
						entries[i].fullUrl = value;
						break;
					case 'Title':
						entries[i].Name = item[3].trim();
						break;
				}
			}

			stationsList.innerHTML = '';
			stationsSelect.innerHTML = '';
			isLoading = true;
			for(let i in entries) {
				// console.log(item[1], ' => ', item[2]);
				if(entries[i].hasOwnProperty('fullUrl')) {
					console.log(entries[i]);
					let idStation = addStation(null, entries[i]);
					count++;
				}
			}
			break;
		case 'text/plain' :
			// const lines = datas.split(/\r\n|\n|\r/);
			const lines = datas.replace(/\}.*?\{/g, '}\n{').split(/\n/);
			if(typeof lines.forEach != 'function') {
				return;
			}
			stationsList.innerHTML = '';
			stationsSelect.innerHTML = '';
			isLoading = true;
			lines.forEach(function(item) {
				try {
					if(item.trim().length > 0) {
						let station = JSON.parse(item.replace(/\t/g, ' ').trim());
						if(station.hasOwnProperty('URL') && station.URL.trim().length > 0) {
							let idStation = addStation(null, station);
							count++;
						}
					}
				} catch(e) {
					console.log('bad line : ' + item);
					console.error(e);
				}
			});
			break;
		default:
			console.log('Unknown format for ' + uri + ' file (' + contentType + ')');
			return;
	}

	if(isConnected && count > 1 && confirm('Do you want to save the ' + count + ' entries of the playlist into the device ?\nThat takes à while. Let\'s be patient !!')) {
		saveStationsList();
	}
}

/* loads playlist from a .m3u, .pls or .txt file */
function loadPlaylist() {
	let input = document.getElementById('loadPlaylist');
	if (input.files.length != 1) {
		return;
	}
	let reader = new FileReader();
	reader.onloadend = function (e) {
		parsePlaylist(input.files[0].type, this.result, input.files[0].name);
	};
	reader.readAsText(input.files.item(0));
}

const xhrPlaylist = new XMLHttpRequest();
xhrPlaylist.onreadystatechange = function() {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			if(this.responseText.length > 0) {
				const tab = document.getElementById('tab-playlist');
				if(tab != null) {
					tab.labels[0].click();
				}
				parsePlaylist(this.getResponseHeader('Content-Type').replace(/;.*$/, ''), this.responseText, this.responseUrl);
			}
			return;
		}
		alert('Error ' + this.status + ':\n' + this.statusText + ' from ' + this.responseURL);
	}
}

function loadPlaylistFromUrl(url) {
	console.log('Downloading a playlist from ' + url);
	xhrPlaylist.open('GET', url);
	xhrPlaylist.send(null);
}

function clearPlaylist() {
	if(isConnected && confirm('Erase all stations ?')) {
		xhrSta.clear();
	}
}

/* ====== Setup hardware for audio output and wifi ======= */

document.forms.hardware.addEventListener('submit', function(event) {
	event.preventDefault();
	xhr.hardware(1);
	alert('System is rebooting..');
})

document.forms.hardware.addEventListener('change', function(event) {
	if(event.target.type == 'range' || (event.target.type == 'radio' && event.target.name == 'spacial')) {
		event.preventDefault();
		xhr.setVS1053(event.target); // Ka-Radio32 just answers 'ok'. No value in return !
		// Hack against Ka-Radio32
		if(event.target.name == 'spacial') { return; }
		const value = event.target.value;
		switch(event.target.name) {
			case 'bassfreq':
				content = value + '0 Hz';
				break;
			case 'treblefreq':
				content = value + ' KHz';
				break;
			default:
				content = value + ' dB';
		}
		event.target.nextElementSibling.innerHTML = content;
	}
})

document.forms.wifi.addEventListener('submit', function(event) {
	event.preventDefault();
	xhr.wifi(1);
})

/* -------------- Sleep / Awake ------- */
document.getElementById('sleep-wake').addEventListener('click', function(event) {
	if(/(?:sleep|wake)Btn/.test(event.target.id)) {
		event.preventDefault();
		const field = document.getElementById(event.target.id.replace(/Btn$/, '-time'));
		if(field != null) {
			// startSleep, stopSleep, startWake, stopWake with websocket
			const value = field.value;
			const action = field.id.replace(/-time$/, '').replace(/^(s|w)/, field.id.charAt(0).toUpperCase());
			if(value.trim().length == 0) {
				websocket.send('stop' + action);
				localTime.removeAttribute('data-' + field.id.replace(/-time$/, ''));
			} else {
				const now = new Date();
				const parts = field.value.split(':');
				const nextDay = (parts[0] <= now.getHours() && parts[1] <= now.getMinutes()) ? 1 : 0;
				const nextDate = new Date(now.getFullYear(), now.getMonth(), now.getDate() + nextDay, parts[0], parts[1], 0);
				let delay = nextDate.getTime() - now.getTime();
				websocket.send('start' + action + "=" + (delay / MINUTES) + '&');
				localTime['user' + action] = nextDate.getTime();
			}
		}
	}
});
/* ============== tabs ============== */

function onTabChange(event) {
	let tabList = document.forms.tabs.elements.tab;
	for (let i = 0, iMax = tabList.length; i < iMax; i++) {
		let label = tabList[i].labels[0];
		if (tabList[i] == this) {
			label.classList.add('active');
		} else {
			label.classList.remove('active');
		}
	}
	switch (this.value) {
		case 'radio':
			displayCurrentStation();
			break;
		case 'settings':
			if(isConnected) { xhr.wifi(); }
			break;
	}
}

function initTabs() {
	let tabList = document.forms.tabs.elements.tab;
	for (let i = 0, iMax = tabList.length; i < iMax; i++) {
		tabList[i].addEventListener('change', onTabChange);
	}

	if (tabList.value == '') {
		let label = tabList[0].labels[0];
		label.click();
	}
}

/* ================ Plugins ================== */

/* loads a plugin on demand */
document.getElementById('main').addEventListener('change', function(event) {
	if(event.target.tagName == 'INPUT' && event.target.name == 'tab' && 'unload' in event.target.dataset) {
		const myScript = document.createElement('SCRIPT');
		if(!confirm('Load "' + event.target.value + '" plugin ?')) { return; }

		event.target.removeAttribute('data-unload');
		myScript.type = 'text/javascript';
		myScript.src = REPO_URL + 'plugins/' + event.target.value + '/index.js?innerHTML=kaPlugin';
		document.head.appendChild(myScript);
	}
});

function kaPlugin(id, content, script) {
	const container = document.getElementById(id);
	if(container != null) {
		container.innerHTML = content;
		container.addEventListener('click', function(event) {
			if(typeof event.target.dataset.stream == 'string') {
				event.preventDefault();
				instantPlayForm.elements.fullUrl.value = event.target.dataset.stream;
				instantPlayForm.elements.instantPlayBtn.click();
			}
		});

		if(typeof script != 'undefined') {
			const myScript = document.createElement('SCRIPT');
			myScript.type = 'text/javascript';
			myScript.src = REPO_URL + 'plugins/' + id + '/script.js';
			document.head.appendChild(myScript);
		}
	}
}

/* ========================= for iframes with CORS policy ============ */
window.addEventListener('message', function(event) {
	if(event.type == 'message' && CLOUD_URL.startsWith(event.origin)) {
		event.preventDefault();
		const payload = JSON.parse(event.data);
		if(payload.hasOwnProperty('playlist')) {
			loadPlaylistFromUrl(payload.playlist);
			return;
		}
	}
});

/* ======= input[type="range"] ==================== */
function displayRangeValue(el) {
	if(
		typeof el.max == 'undefined' ||
		el.max.length == 0 ||
		typeof el.min == 'undefined' ||
		el.min.length == 0
	) { return; }

	const range = parseInt(el.max) - parseInt(el.min);
	const ratio = (el.valueAsNumber - parseInt(el.min)) / range;
	const caption = el.nextElementSibling;
	caption.textContent = Math.round(100 * el.valueAsNumber / range) + '%';
	caption.style.left = Math.round(el.offsetLeft + el.offsetWidth * ratio) + 'px';
}

if(matchMedia('(min-width: 48rem)').matches) {
	const inputRanges = document.querySelectorAll('input[type="range"]:not(.no-cursor)');
	if(inputRanges.length > 0) {
		for(let i=0, iMax=inputRanges.length; i<iMax; i++) {
			const caption = document.createElement('SPAN');
			caption.textContent = '';
			caption.className = 'range-value';
			const el = inputRanges[i];
			if(el.nextElementSibling != null) {
				el.parentElement.insertBefore(caption, el.nextElementSibling);
			} else {
				el.parentElement.appendChild(caption);
			}
			el.parentElement.style.position = 'relative';
			displayRangeValue(el);

			el.addEventListener('input', function(event) {
				event.preventDefault();
				displayRangeValue(event.target);
			});
		}
	}
}

/* ============= Init ======================== */

const REPO_URL = document.scripts[0].src.replace(/\/\w+\/script\.js$/, '/');
console.log('REPO_URL = ', REPO_URL);

const CLOUD_URL = 'https://bazooka07.github.io/Ka-Radio32/'; // must end with '/'

// Update urls for the version and playlists in the cloud
['version32', 'infos'].forEach(function(item){
	const el = document.getElementById('frame-' + item);
	if(el != null) {
		el.src = CLOUD_URL + item+ '.html';
	}
});

if(document.body.hasAttribute('data-ip')) {
	IP_DEVICE = document.body.dataset.ip;
	console.log('URI for the device : ', IP_DEVICE);
}

// Display the first tab
initTabs();
document.forms.tabs.elements.tab[0].checked = true;

// getVersion launches each function if success
xhr.getVersion();
