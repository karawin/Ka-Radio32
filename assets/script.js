'use strict';

/*
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

var isLoading = true; // displayed webradios are not saving in the Ka-Radio device

// https://github.com/karawin/Ka-Radio32/wiki#html-interface-for-the-wifi-webradio

function setCustomHeader(xhr, action) {
	if(typeof IP_DEVICE == 'string') {
		xhr.setRequestHeader('Karadio-Action', action);
	}
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
	for (var value in icy) {
		const target = document.getElementById('icy-' + value);
		if (target != null) {
			switch (value) {
				case 'auto':
					target.checked = (icy[value] == 1);
					break;
				case 'curst':
				case 'vol':
					target.value = icy[value];
					if (value == 'curst') {
						currentStationId = icy[value];
					}
					break;
				case 'not1':
				case 'not2':
				case 'descr':
					target.innerHTML = icy[value].replace(/<br\s*\/?>/i, '').trim();
					break;
				case 'bitr':
					target.textContent = icy[value].trim() + ' kB/s';
					break;
				case 'url1':
					target.href = ((/^https?:\/\//.test(icy.url1.trim())) ? '' : 'http://') + icy.url1.trim();
				default:
					target.textContent = icy[value].trim();
			}
		} else {
			console.log('icy-' + value + ' element not found');
		}
	}
	const playing = (icy.name.trim().length > 0);
	stationsBtn.playing = playing;
	stationsBtn.textContent = (playing) ? 'Stop' : 'Play';
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
			if(!isLoading) {
				xhr.valueChange(this.dataset.action, this.dataset.param + '=' + value + '&'); // Hack against Ka-Radio
			} else {
				// stations in the playlist table and select are from a file, not from the Ka-Radio device
				const row = document.getElementById('station-' + value) ;
				if(row != null) {
					instantPlayForm.elements.fullUrl.value = row.cells[2].textContent;
					instantPlayForm.elements.instantPlayBtn.click();
				}
			}
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
		console.log('Bad URL : ' + fullUrl);
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
	// console.log('Instant play', fullUrl);

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
	// Créer un évenement change pour StationsSelect
	console.log('Play station');
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
			this.send('opencheck');
		}

		websocket.onmessage = function (event) {
			try {
				let msg = JSON.parse(event.data);
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
				console.log('Error on message: ', err);
			}
		}

		websocket.onclose = function (event) {
			console.log(this.url + ' closed');
		}

		websocket.onerror = function (event) {
			console.log('Websocker error: ', event.originalTarget);
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
				delayTimes[i].textContent = (delay <= 0) ? '&nbsp;' : new Date(delay).toISOString(11, 8);
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
	for (let i = 0, iMax = stationsList.rows.length; i < iMax; i++) {
		if (stationsList.rows[i].id != 'station-' + i) {
			stationsList.rows[i].id = 'station-' + i;
			stationsList.rows[i].cells[0].textContent = i;
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
		stationId = 0;
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

	if(!datas.hasOwnProperty('fullUrl')) {
		let port = '';
		if(datas.hasOwnProperty('Port') && datas.Port.trim() != '80') {
			port = ':' + datas.Port.trim();
		}
		datas.fullUrl = datas.URL + port + datas.File;
	}

	let tr = document.createElement('TR');
	tr.id = 'station-' + stationId;
	tr.draggable = true;

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

	urlCell.textContent = ((/^https?:\/\//.test(datas.fullUrl)) ? '' : 'http://') + datas.fullUrl;
	volCell.textContent = (datas.hasOwnProperty('ovol')) ? datas.ovol : '0';
	tr.appendChild(urlCell);
	tr.appendChild(volCell);
	stationsList.appendChild(tr);
	setDrapAndDrop(tr);
	return stationId;
}

function getVersion(release) {
	// GET, /?version - Ex: Release: 1.9, Revision: 5
	let xhrVersion = new XMLHttpRequest();
	xhrVersion.onreadystatechange = function() {
		const PATTERN = /^release\b.*?(\d+)\.(\d+).*?(\d+).*/i;
		if(
			this.readyState === XMLHttpRequest.DONE && this.status === 200 &&
			this.getResponseHeader('Content-Type').startsWith('text/') &&
			PATTERN.test(this.responseText)
		) {
			const el = document.getElementById('version');
			el.textContent = this.responseText.trim().replace(PATTERN, 'Ver. $1.$2.$3');
		}
	};
	let url = (typeof IP_DEVICE != 'string') ? '/' : window.location.href;
	xhrVersion.open('GET', url + '?version');
	xhrVersion.send();
}

/* ----------- display current station ---------------- */
const xhrCurst = new XMLHttpRequest();
xhrCurst.onreadystatechange = function () {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			// console.log(this.responseText);
			if(this.responseText.trim().length === 0 || !this.getResponseHeader('Content-Type').startsWith('application/json')) { return; }

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
	const action = 'icy';
	const url = (typeof IP_DEVICE != 'string') ? '/' + action : window.location.href;
	xhrCurst.open('POST', url);
	xhrCurst.setRequestHeader('Content-Type', contentTypeForm);
	setCustomHeader(xhrCurst, action);
	xhrCurst.send(null);
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

	const action = 'hardware';
	const url = (typeof IP_DEVICE != 'string') ? '/' + action : window.location.href;
	xhrHardware.open('POST', url);
	xhrHardware.setRequestHeader('Content-Type', contentTypeForm);
	setCustomHeader(xhrHardware, action);
	xhrHardware.send(params.join('&'));
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
	let params = 'nb=1&id=' + stationId + '&name=' + datas.Name + '&url=' + datas.URL + '&port=' + datas.port + '&file=' + datas.file + '&ovol=' + datas.ovol;
	// let params = 'id=' + stationId + '&name=' + datas.Name + '&url=' + datas.URL + '&port=' + datas.port + '&file=' + datas.file + '&ovol=' + datas.ovol;
	this.sendForm('setStation', params);
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
	/*
	 * No working with fullUrl = http://5.135.154.69:12500/;
	 * curl 'http://192.168.58.77?instant=http://5.135.154.69:12500/;' doesn't work
	 * curl 'http://192.168.58.77?instant=http%3A%2F%2F5.135.154.69%3A12500%2F%3B' doesn't work
	 * but curl -d 'url=5.135.154.69' -d 'port=12500' -d 'path=/;' http://192.168.58.77/instant_play is right
	 * idem with http://87.118.126.101:19406/stream from http://yp.shoutcast.com/sbin/tunein-station.m3u?id=1683077
	 * */

	// this.sendCommand('instant', encodeURI(fullUrl.replace(/^https/, 'http')));

	// hack against Ka-Radio
	const matches = fullUrl.match(/^https?:\/\/([^:/]+)(?::(\d+))?(.*)/);
	if(matches != null) {
		if(typeof matches[2] == 'undefined') {
			matches[2] = '80';
		}
		if(!matches[3].startsWith('/')) {
			matches[3] = '/' + matches[3];
		}
		xhr.sendForm('instant_play', 'url=' + matches[1] + '&port=' + matches[2] + '&path=' + matches[3]);
	}
}
xhr.valueChange = function (action, params) {
	this.sendForm(action, params);
}
xhr.wifi = function (valid) {
	if (typeof valid == 'undefined') {
		valid = '0';
	}
	let params = [
		'valid=' + valid
	];
	[
		'ssid',
		'ssid2',
		'pasw',
		'pasw2',
		'dhcp',
		'dhcp2',
		'ip',
		'msk',
		'gw',
		'ip2',
		'msk2',
		'gw2',
		'ua',
		'host',
		'tzo'
	].forEach(function (name) {
		let el = document.forms.wifi.elements[name];
		if (el != null) {
			params.push(name + '=' + el.value);
		} else {
			console.log('No input with name=' + name);
		}
	});
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
		if(device == '4') {
			// VS1053
			alert('VS1053 is not still supported');
		}
	}
	this.sendForm('hardware', params.join('&'));
}
xhr.onreadystatechange = function () {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			// console.log(this.responseText);
			if (this.responseText.trim().length === 0) {
				return;
			}

			if(!this.getResponseHeader('Content-Type').startsWith('application/json')) { return; }

			let datas = JSON.parse(this.responseText);
			// console.log(datas);
			if ('curst' in datas) {
				icyDisplay(datas);
				meta.textContent = datas.meta;
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

			console.log('Error: %d (%s)', this.status, this.statusText);
		} else {
			console.log('Error ' + this.status + ': ' + this.statusText + ' from ' + this.responseURL);
		}
	}
}

/* -------- download all the stations from the Ka-Radio device --------- */
const xhrSta = new XMLHttpRequest();

xhrSta.loadStation = function (stationId) {
	if (typeof stationId === 'number') {
		this.stationId = stationId;
	};
	progressBar.value = this.stationId;

	const action = 'getStation';
	const url = (typeof IP_DEVICE != 'string') ? '/' + action : window.location.href;
	const params = 'idgp=' + this.stationId;

	this.open('POST', url);
	this.setRequestHeader('Content-Type', contentTypeForm);
	setCustomHeader(this, action);
	this.send(params);
}

xhrSta.onreadystatechange = function () {
	if (this.readyState === XMLHttpRequest.DONE) {
		if (this.status === 200) {
			// console.log(this.responseText);
			if(
				this.responseText.trim().length === 0 ||
				!this.getResponseHeader('Content-Type').startsWith('application/json')
			) { return; }

			let datas = JSON.parse(this.responseText);
			// console.log(datas);
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
						isLoading = false;
					}
				}
				return;
			}
		}
		console.error(this.status, this.statusText + ' from ' + this.responseURL);
	}
}

function loadStationsList() {
	if (stationsList == null) { return; }

	stationsList.innerHTML = '';
	stationsSelect.innerHTML = '';
	progressBar.max = MAX_STATIONS;
	xhrSta.loadStation(0);
}

function saveStationsList() {
	const BATCH_SIZE = 8;
	let saveStationsTimer = null;
	let saveStationId = -1;

	const xhrPlaylistSave = new XMLHttpRequest();
	xhrPlaylistSave.clear = function() {
		const action = 'clear';
		let url = '/' + action;
		let params = '';
		if(typeof IP_DEVICE == 'string') {
			let extra = 'action=' + action;
			if(params.length == 0) {
				params = extra;
			} else {
				params += '&' + extra;
			}
			url = window.location.href;
		}
		this.open('POST', url);
		this.setRequestHeader('Content-Type', contentTypeForm);
		setCustomHeader(this, action);
		this.send();
	};

	xhrPlaylistSave.saveStation = function() {
		if(saveStationsTimer != null) {
			clearTimeout(saveStationsTimer);
			saveStationsTimer = null;
		}

		const output = new Array();
		for(let i=0; i<BATCH_SIZE; i++) {
			var endOfStations = false;
			let row = null;
			let url = '';
			do {
				saveStationId++;
				if(saveStationId >= MAX_STATIONS) { break; }
				row = stationsList.querySelector('#station-' + saveStationId);
				if(row != null) {
					url = row.cells[2].textContent.replace('&nbsp;', ' ').trim();
				}
			} while(url.length == 0);

			if(url.length == 0) { break; }
			let datas = extractFullUrl(url);

			output.push('id=' + saveStationId + '&name=' + row.cells[1].textContent + '&url=' + datas.url + '&port=' + datas.port + '&file=' + datas.path1 + '&ovol=' + row.cells[3].textContent.trim() + '&');
		}

		// Check if output not empty
		if(output.length == 0) {
			isLoading = false;
			console.log('Playlist saved');
			return;
		}

		let params = 'nb=' + output.length + '&' + output.join('&');
		const action = 'setStation';
		let url = '/' + action;
		if(typeof IP_DEVICE == 'string') {
			let extra = 'action=' + action;
			if(params.length == 0) {
				params = extra;
			} else {
				params += '&' + extra;
			}
			url = window.location.href;
		}

		console.log(url, '=>', params);
		this.open('POST', url);
		this.setRequestHeader('Content-Type', contentTypeForm);
		setCustomHeader(this, action);
		this.send(params);
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

	// xhrPlaylistSave.saveStation(1);
	xhrPlaylistSave.clear();
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
	let datas = extractFullUrl(this.elements.urlStation.value);
	xhr.saveStation(idStation, {
		Name: this.elements.nameStation.value,
		URL: datas.url,
		port: datas.port,
		// file: encodeURI(datas.path1),
		file: datas.path1,
		ovol: this.elements.volStation.value
	});

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

function parsePlaylist(contentType, datas) {
	// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/matchAll
	let matches = null;
	let count = 0;
	switch(contentType) {
		case 'audio/x-mpegurl' :
			if(!/^#EXTM3U\b/.test(this.result)) {
				console.log('Bad syntax. Missing #EXTM3U at the beginning of file');
				return;
			}

			stationsList.innerHTML = '';
			stationsSelect.innerHTML = '';
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
			if(!/^\[playlist\]/.test(this.result)) {
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
			const lines = datas.split(/\r\n|\n|\r/);
			if(typeof lines.forEach != 'function') {
				return;
			}
			stationsList.innerHTML = '';
			stationsSelect.innerHTML = '';
			lines.forEach(function(item) {
				try {
					if(item.trim().length > 0) {
						let station = JSON.parse(item.trim());
						if(station.hasOwnProperty('URL') && station.URL.trim().length > 0) {
							console.log(station);
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
			console.log('Unknown format for ' + input.files[0].name + ' file (' + input.files[0].type + ')');
			return;
	}

	isLoading = true;
	if(count > 1 && confirm('Do you want to save the ' + count + ' entries of the playlist into the device ?\nThat takes à while. Let\'s be patient !!')) {
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
		parsePlaylist(input.files[0].type, this.result);
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
				parsePlaylist(this.getResponseHeader('Content-Type').replace(/;.*$/, ''), this.responseText);
			}
			return;
		}
		console.error(this.status + ': ' + this.statusText + ' from ' + this.responseURL);
	}
}

function loadPlaylistFromUrl(url) {
	console.log('Downloading a playlist from ' + url);
	xhrPlaylist.open('GET', url);
	xhrPlaylist.send(null);
}

function clearPlaylist() {
	if(confirm('Erase all stations ?')) {
		alert('Clear the playlist');
	}
}

/* ====== Setup hardware for audio output and wifi ======= */

document.forms.hardware.addEventListener('submit', function(event) {
	event.preventDefault();
	xhr.hardware(1);
	alert('System is rebooting..');
})

document.forms.wifi.addEventListener('submit', function(event) {
	event.preventDefault();
	const lines = ['valid=1'];
	const elements = event.target.elements;
	['', '2'].forEach(function(col) {
		let dhcp = false;
		['ssid', 'pasw', 'dhcp', 'ip', 'msk', 'gw', 'ua', 'host', 'tzo'].forEach(function(field) {
			if(col == '2' && ['ua', 'host', 'tzo'].indexOf(field) >= 0) { return; }
			if(!dhcp && ['ip', 'msk', 'gw'].indexOf(field) >= 0) { return; }
			const el = elements.namedItem(field + col);
			if(field == 'dhcp') {
				dhcp = el.checked;
				if(dhcp) { lines.push('dhcp' + col + '=true'); }
			} else {
				lines.push(el.name + '=' + el.value);
			}
		});
	});
	xhr.sendForm('wifi', lines.join('&'));
})

/* -------------- Sleep / Awake ------- */
document.getElementById('sleep-wake', function(event) {
	if(/(?:sleep|wake)Btn/.test(event.target.id)) {
		event.preventDefault();
		const field = document.getElementById(event.target.id.replace(/Btn$/, '-time'));
		if(field != null) {
			// startSleep, stopSleep, startWake, stopWake with websocket
			const value = field.value;
			const action = field.name.replace(/-time$/, '').replace(/^(s|w)/, '$1').toUpperCase();
			if(value.trim().length == 0) {
				websocket.message('stop' + action);
				localTime.removeAttribute('data-' + field.name.replace(/-time$/, ''));
			} else {
				const now = new Date();
				const parts = fied.value.split(':');
				const nextDay = (parts[0] <= now.getHours() && parts[1] <= now.getMinutes()) ? 1 : 0;
				const nextDate = new Date(now.getFullYear(), now.getMonth(), now.getDate() + nextDay, parts[0], parts[1], 0);
				let delay = nextDate.getTime() - now.getTime();
				websocket.message('start' + action + "=" + (delay / MINUTES) + '&');
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
			xhr.wifi();
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

initTabs();

/* ================ Plugins ================== */

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
/* ============= Init ======================== */

const REPO_URL = document.scripts[0].src.replace(/\/\w+\/script\.js$/, '/');
console.log('REPO_URL = ', REPO_URL);

// Update urls for the playlists in the cloud
const frameInfos = document.getElementById('frame-info');
frameInfos.src = (frameInfos != null) ? REPO_URL + 'infos.html' : 'http://karadio.karawin.fr/infos.php';

if(document.body.hasAttribute('data-ip')) {
	IP_DEVICE = document.body.dataset.ip;
	console.log('IP Address for the device : ', IP_DEVICE);
}

// Display the first tab
document.forms.tabs.elements.tab[0].checked = true;

openSocket();
displayCurrentStation();
getVersion();
displayHardware();
setRssiInterval();
loadStationsList();

// for iframes with CORS policy
window.addEventListener('message', function(event) {
	if(event.type == 'message' && REPO_URL.startsWith(event.origin)) {
		event.preventDefault();
		const payload = JSON.parse(event.data);
		if(payload.hasOwnProperty('playlist')) {
			loadPlaylistFromUrl(payload.playlist);
			return;
		}

		console.error(payload);
	}
});
