// https://de1.api.radio-browser.info/

(function() {
	const URL_BASE = 'https://de1.api.radio-browser.info/json/';

	const myForm = document.forms.namedItem('radioBrowser');
	const countriesSelect = document.forms.namedItem('radioBrowser').elements.country;
	const languagesSelect = document.forms.namedItem('radioBrowser').elements.language;
	const statesSelect	  = document.forms.namedItem('radioBrowser').elements.state;
	const playlist = document.getElementById('rb-stations').querySelector('table tbody');
	// 'id changeuuid stationuuid name url url_resolved homepage favicon tags country countrycode state language votes lastchangetime ip codec bitrate hls lastcheckok lastchecktime lastcheckoktime clicktimestamp clickcount clicktrend'
	const COLUMNS = {
		favicon 		: ' ',
		name			: 'Name',
		tags			: 'Tags',
		codec			: 'Codec',
		bitrate			: 'Bit-rate',
		url				: 'Stream',
		countrycode		: 'Country Code',
		state			: 'State',
		language		: 'Lang.',
		lastchangetime	: 'Last change',
		lastcheckoktime	: 'Last check'
	};

	var states = null;

	myForm.addEventListener('submit', function(event) {
		event.preventDefault();
		playlist.textContent = '';
		const xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (this.readyState === XMLHttpRequest.DONE) {
				if(this.status === 200) {
					const stations = JSON.parse(this.responseText);
					console.log('Ok for ' + stations.length + ' stations from http://radio-browser.info');
					// E.G.: https://de1.api.radio-browser.info/json/stations/byname/rdwa

					stations.forEach(function(item) {
						const row = document.createElement('TR');

						for(k in COLUMNS) {
							const cell = document.createElement('TD');
							switch(k) {
								case 'favicon'	: cell.innerHTML = '<img src="' + item.favicon + '" title="' + item.stationuuid + '" data-playable="' + item.stationuuid + '"/>'; break;
								case 'name'		: cell.innerHTML = (item.homepage.trim().length > 0) ? '<a href="' + item.homepage + '" target="_blank">' + item.name.trim() + '</a>' : item.name.trim(); break;
								case 'url'		: cell.innerHTML = '<a href="' + item.url + '" data-stream="' + item.url + '">Listen</a>'; break;
								case 'language'	: cell.innerHTML = item.language.replace(/\s+/g, '&nbsp;').replace(/\s*,\s*/g, ' '); break;
								case 'tags'		: cell.innerHTML = (item.tags.trim().length > 0) ? '<span>' + item.tags.replace(/\s*,\s*/g, '</span> <span>') + '</span>' : '&nbsp;'; break;
								default:
									if([0, '0', 'UNKNOWN'].indexOf(item[k]) < 0) {
										cell.textContent = item[k];
									} else {
										cell.innerHTML = '&nbsp;';
									}
							}
							row.appendChild(cell);
						}

						playlist.appendChild(row);
					});
				} else {
					console.log('radiobrowser error code ' + this.status, this.statusText);
				}
			}
		};

		playlist.addEventListener('click', function(event) {
			if(event.target.tagName == 'SPAN' && !event.target.dataset.hasOwnProperty('stream')) {
				event.preventDefault();
				switch(event.target.parentElement.cellIndex) {
					case 2:
						const form1 = document.forms.namedItem('radioBrowser');
						form1.elements.tag.value = event.target.textContent;
						form1.elements.submit.click();
						break;
				}
			}
		});

		const params = new URLSearchParams({limit: 500});
		['name', 'state', 'country', 'language', 'tag'].forEach(function(item) {
			const entry = event.target.elements[item];

			if(entry.tagName == 'SELECT' && entry.selectedIndex > 0) {
				params.append(item, entry.value);
				return;
			}

			value = entry.value.trim();
			if(value.length > 0) {
				params.append(item, value);
			}
		});

		console.log('Request stations with ' + params.toString());
		xhr.open('GET', URL_BASE + 'stations/search?' + params.toString());
		xhr.send();
	});

	countriesSelect.addEventListener('change', function(event) {
		statesSelect.innerHTML = '<option value="">---</option>';

		const value = event.target.value.trim();
		if(states != null && value.length > 0 && states.hasOwnProperty(value)) {
			for(var i in states[value]) {
				const option = document.createElement('OPTION');
				option.textContent = i + ' (' + states[value][i] + ')';
				option.value = i;
				statesSelect.appendChild(option);
			}
		}
	});

	function setHeadColumns() {
		const head = document.getElementById('rb-stations').querySelector('table thead');
		for(item in COLUMNS) {
			const cell = document.createElement('TH');
			cell.textContent = COLUMNS[item];
			head.appendChild(cell);
		}
	}

	function getStates() {
		const xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (this.readyState === XMLHttpRequest.DONE) {
				if(this.status === 200) {
					const datas = JSON.parse(this.responseText);
					console.log(datas.length + ' states from http://radio-browser.info');

					states = {};
					datas.forEach(function(item) {
						if(item.hasOwnProperty('country')) {
							const country = item.country.trim();
							if(country.length == 0) { return; }

							if(!states.hasOwnProperty(country)) {
								states[country] = {};
							}
							states[country][item.name] = item.stationcount;
						} else {
							console.log('Bad state : ', item);
						}
					});
				} else {
					console.log('radiobrowser error code ' + this.status, this.statusText);
				}
			}
		};
		xhr.open('GET', URL_BASE + 'states');
		xhr.send();
	}

	function getCountries() {
		const xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (this.readyState === XMLHttpRequest.DONE) {
				if(this.status === 200) {
					const countries = JSON.parse(this.responseText);
					console.log(countries.length + ' countries from http://radio-browser.info');
					countries.forEach(function(item) {
						const option = document.createElement('OPTION');
						option.value = item.name;
						option.innerHTML = item.name + ' (<em>' + item.stationcount + '</em>)';
						countriesSelect.appendChild(option);
					});

					getStates();
				} else {
					console.log('radiobrowser error code ' + this.status, this.statusText);
				}
			}
		};
		xhr.open('GET', URL_BASE + 'countries');
		xhr.send();
	}

	function getLanguages() {
		const xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (this.readyState === XMLHttpRequest.DONE) {
				if(this.status === 200) {
					const items = JSON.parse(this.responseText);
					console.log(items.length + ' languages  from http://radio-browser.info');
					items.forEach(function(item) {
						const option = document.createElement('OPTION');
						option.value = item.name;
						option.textContent = item.name + ' (' + item.stationcount + ')';
						languagesSelect.appendChild(option);
					});
				} else {
					console.log('radiobrowser error code ' + this.status, this.statusText);
				}
			}
		};
		xhr.open('GET', URL_BASE + 'languages');
		xhr.send();
	}

	setHeadColumns();
	getCountries();
	getLanguages();

})();
