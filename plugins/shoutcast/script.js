// http://wiki.shoutcast.com/wiki/SHOUTcast_Radio_Directory_API

const Shoutcast = function() {
	'use strict';

	const YELLOW_PAGES_SHOUTCAST = 'https://yp.shoutcast.com';
	const API_URL = 'https://api.shoutcast.com/';

	let stationsList, stationsIndex;
	let stationsTimer = null;
	let ticking = false;

	const stationsStep = 20;
	const genreList =	document.getElementById('sh-genrelist-0');
	const playlist =	document.getElementById('sh-playlist');
	const genreTitle =	document.getElementById('sh-title');
	const genreIds = {};

	function setGenreTitle(name) {
		genreTitle.innerHTML = name + ' (<em id="stations-list-count"> ... </em>)';
		stationsList = null;
		playlist.textContent = '';
	}

	function on_playClick(event) {
		// Play the stream under the img tag
		if(event.target.tagName == 'IMG' && 'stationid' in event.target.dataset) {
			event.preventDefault();
			let stationId = event.target.dataset.stationid;
			// let url = YELLOW_PAGES_SHOUTCAST + stationsList.tunein.base + '?id=' + stationId;
			let url = YELLOW_PAGES_SHOUTCAST + '/sbin/tunein-station.m3u?id=' + stationId;
			instantPlayForm.elements.fullUrl.value = url;
			instantPlayForm.elements.instantPlayBtn.click();
			return;
		}

		// Search stations for a musical genre in full text
		if(event.target.tagName == 'SPAN' && event.target.parentElement.classList.contains('genres')) {
			event.preventDefault();
			const caption = event.target.textContent.trim();
			if(caption in genreIds) {
				const genreId = genreIds[caption]
				const genreRadio = document.getElementById('sh-genre-' + genreId);
				if(genreRadio != null) {
					genreRadio.checked = true;
					setGenreTitle(caption);
					if(genreRadio.name != 'sh-radio-genre-0') {
						const parent = document.getElementById(genreRadio.name.replace(/^sh-radio-genre/, 'sh-genre'))
						parent.checked = true;
					}
				}
				createScript('advancedSearch', { genre_id: genreId });
			} else {
				console.log(value + ' genre not found');
			}
		}
	};

	function on_scroll(event) {
		if(ticking) { return; }
		ticking = true;
		// if(event.target.scrollTopMax - event.target.scrollTop < 300) { // only for Mozilla
		const el = event.target;
		if(el.scrollHeight - el.scrollTop - el.clientHeight < 300) {
			displayStationsList(true);
		}
		stationsTimer = setTimeout(
			function() {
				clearTimeout(stationsTimer);
				ticking = false;
			}, 500
		);
	}

	function displayStationsList(more) {
		if(stationsList == null || typeof stationsList.station.forEach == 'undefined') { return; }

		if(typeof more == 'undefined') {
			stationsIndex = 0;
		} else if(typeof more == 'boolean' && more) {
			if(stationsIndex + stationsStep >= stationsList.station.length) { return; }
			stationsIndex += stationsStep;
		} else {
			return;
		}

		stationsList.station.slice(stationsIndex, stationsIndex + stationsStep).forEach(function(item, index) {
			if(typeof item.id == 'undefined') { return; }

			let station = document.createElement('FIGURE');
			station.id = 'station-' + (stationsIndex + index);
			let title = document.createElement('FIGCAPTION');
			title.classList = 'center';
			title.innerHTML = item.name.replace(/,\s*/g, ', ').replace(/(\w)\s*\+\s*(\w)/g, '$1 + $2').replace(/_/g, ' ');
			station.appendChild(title);

			let div1 = document.createElement('DIV');
			div1.className = 'infos';

			let div11 = document.createElement('DIV');
			let img = document.createElement('IMG');
			img.src = (typeof item.logo == 'string') ? item.logo : REPO_URL + 'assets/play.png';
			img.alt = 'No logo';
			img.setAttribute('data-stationid', item.id);
			div11.appendChild(img);
			div1.appendChild(div11);

			let div12 = document.createElement('DIV');

			let br = document.createElement('P');
			br.textContent = item.br + ' Kb/s';
			div12.appendChild(br);

			let mt = document.createElement('P');
			mt.textContent = item.mt;
			div12.appendChild(mt);

			let lc = document.createElement('P');
			let content = item.lc;
			if('ml' in item) {
				content += '/' + item.ml;
			}
			lc.textContent = content + ' listeners';
			div12.appendChild(lc);

			div1.appendChild(div12);
			station.appendChild(div1);

			let div2 = document.createElement('DIV');
			div2.className = 'current';

			if('ct' in item) {
				let ct = document.createElement('P');
				ct.innerHTML = item.ct;
				div2.appendChild(ct);
			}

			if('cst' in item) {
				let cst = document.createElement('P');
				cst.innerHTML = item.cst;
				div2.appendChild(cst);
			}

			station.appendChild(div2);

			let genres = document.createElement('DIV');
			genres.className = 'genres';
			let genre = document.createElement('SPAN');
			genre.textContent = item.genre;
			genres.appendChild(genre);
			for(let i=2; i<8; i++) {
				let k = 'genre' + i;
				if(k in item) {
					let content = item[k].trim();
					if(content.length > 0) {
						let nextGenre = document.createElement('SPAN');
						nextGenre.innerHTML = content;
						genres.appendChild(nextGenre);
					}
				}
			}
			station.appendChild(genres);

			playlist.appendChild(station);
		});
		stationsIndex += stationsStep;
	}

	function on_genreChange(event) {
		if(event.target.tagName == 'INPUT' && event.target.type == 'radio') {
			if(event.target.id.startsWith('sh-genre-')) {

				const subGenres = document.getElementById('sh-genrelist-' + event.target.value);
				if(subGenres != null) {
					const activeSubGenre = subGenres.querySelector('input:checked');
					if(activeSubGenre != null) {
						activeSubGenre.checked = false;
					}
				}

				setGenreTitle(event.target.labels[0].textContent);

				if(event.target.value != '-1') {
					createScript('advancedSearch', { genre_id: event.target.value });
				} else {
					createScript('advancedSearch', { mt: 'mpeg' });
				}
			}
		}
	}

	/* ----------- adanced search for stations --- */
	this.cb_advancedSearch = function(datas) {
		if(! 'response' in datas) {
			console.log('Error from ' + API_URL);
			return;
		}
		if(datas.response.statusCode != 200) {
			console.log('Error from ' + API_URL + ': ' + datas.response.statusCode + ' ' + datas.response.statusText);
			console.log(datas.response.statusDetailText);
			return;
		}

		playlist.classList.remove('loading');

		let el = document.getElementById('stations-list-count');
		if(el != null) {
			let content = 'No station';
			if('station' in datas.response.data.stationlist) {
				if(typeof datas.response.data.stationlist.station.forEach == 'function') {
					content = datas.response.data.stationlist.station.length + ' stations';
					stationsList = datas.response.data.stationlist;
				} else {
					content = 'Just one station';
					stationsList = {
						station: [ datas.response.data.stationlist.station ],
						tunein: datas.response.data.stationlist.tunein
					};
				}

				displayStationsList();
			}
			el.textContent = content;
		}

	}

	/* ----------- download each genre ----------- */
	function addGenre(item) {
		let genrelistParent = document.getElementById('sh-genrelist-' + item.parentid);
		if(genrelistParent == null) { return; }

		let radioBtn = document.createElement('INPUT');
		radioBtn.type = 'radio';
		radioBtn.name = 'sh-radio-genre-' + item.parentid;
		radioBtn.id = 'sh-genre-' + item.id;
		radioBtn.value = item.id;

		let label = document.createElement('LABEL');
		label.setAttribute('for', radioBtn.id);
		label.innerHTML = item.name; // Don't use textContent ! html entities in the datas in json format (R&B and Urban)

		let li = document.createElement('LI');
		li.appendChild(radioBtn);
		li.appendChild(label);

		genrelistParent.appendChild(li);

		genreIds[item.name] = item.id;

		if(item.haschildren && item.genrelist.genre.length > 0) {
			// radioBtn.setAttribute('data-children', '1');
			let ul = document.createElement('UL');
			ul.id = 'sh-genrelist-' + item.id;
			li.appendChild(ul);
			item.genrelist.genre.forEach(addGenre);
		}
	}

	this.cb_genreList = function(datas) {
		if(! 'response' in datas) {
			console.log('Error from ' + API_URL);
			return;
		}
		if(datas.response.statusCode != 200) {
			console.log('Error from ' + API_URL + ': ' + datas.response.statusCode + ' ' + datas.response.statusText);
			console.log(datas.response.statusDetailText);
			return;
		}

		datas.response.data.genrelist.genre.forEach(addGenre);

		genreList.addEventListener('change', on_genreChange);
		document.getElementById('sh-genre-top500').click();
	}

	function createScript(callback, params) {
		if(typeof callback == 'undefined' || callback.trim().length == 0) {
			console.log('callback function for Shoutcast is not defined');
			return;
		}

		const query = new URLSearchParams((typeof params == 'undefined') ? '' : params);
		query.append('k', 'JOgXcgT7bQNw6zV2');
		query.append('f', 'json');

		if(callback != 'nowPlaying') {
			query.append('c', 'myShoutcast.cb_' + callback);
		}
		if(callback != 'genreList') {
			playlist.textContent = '';
			playlist.classList.add('loading');
		}

		let url = null;
		switch(callback) {
			case 'genreList' :
				url = 'genre/secondary';
				break;
			case 'advancedSearch' :
				url = 'station/advancedsearch';
				break;
			case 'nowPlaying':
				url = 'station/nowplaying';
				query.append('c', 'myShoutcast.cb_' + 'advancedSearch');
		}
		if(url == null) {
			console.log('No url for ' + API_URL);
			return;
		}

		let id = 'sh-' + callback.replace('/', '-');
		let myScript = document.scripts.namedItem(id);
		if(myScript != null) { document.head.removeChild(myScript); }
		myScript = document.createElement('SCRIPT');
		myScript.type = 'text/javascript';
		myScript.id = id;
		const src = API_URL + url + '?' + query.toString();
		myScript.src = src;
		// console.log(src);
		document.head.appendChild(myScript);
	}

	playlist.addEventListener('click', on_playClick);
	playlist.addEventListener('scroll', on_scroll);
	document.forms.sh_search.addEventListener('submit', function(event) {
		event.preventDefault();
		const el = document.forms.sh_search.elements.query;
		if(el.value.trim().length > 0) {
			setGenreTitle(el.value);
			createScript('nowPlaying', { ct: el.value });
			document.getElementById('sh-genre-top500').checked = true;
		}
	});

	createScript('genreList', { parentid: '0'} );
};

myShoutcast = new Shoutcast();
