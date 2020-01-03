(function() {
	'use strict';

	/*
	 * https://api.calmradio.com/v2/channels.json?locale=en
	 * https://api.calmradio.com/v2/metadata.json?locale=en
	 * https://arts.calmradio.com
	 * */

	const API_URL = 'https://api.calmradio.com/v2';
	const ARTS_URL = 'https://arts.calmradio.com';
	const locale = navigator.language.substr(0, 2);

	const rowsContainer = document.getElementById('calmradio-metadata');
	if(rowsContainer == null) {
		console.log('#calmradio-metadata element not found');
		return
	}

	const channelsContainer = document.getElementById('calmradio-channels');
	if(channelsContainer == null) {
		console.log('#calmradio-channels element not found');
		return
	}

	var channels = null;
	function getChannels() {
		const xhrMetaDatas = new XMLHttpRequest();
		xhrMetaDatas.onreadystatechange = function () {
			if (this.readyState === XMLHttpRequest.DONE) {
				if (this.status === 200) {
					const datas = JSON.parse(this.responseText).channels;
					channels = {};
					datas.forEach(function(channel) {
						channels[channel.id] = channel;
					});

					console.log('Channels loaded from ' + API_URL);
					const rows = document.querySelectorAll('input[name="rows"]');
					if(rows.length > 0) {
						// metadata are loaded
						rows[0].click();
					} else {
						console.log('Metadata are not loaded');
					}
					return;
				}

				console.log('Error #', this.status, this.statusText);
			}
		};

		xhrMetaDatas.open('GET', API_URL + '/channels.json?locale=' + locale);
		xhrMetaDatas.send();
	}

	function addCategory(parent, category) {
		const id = 'category-' + category.id;
		const title = 'category #' + category.id;
		const caption = (category.thumb != null) ? '<img src="" data-src="' + ARTS_URL + category.thumb + '" alt="' + category.title + '" title="' + title + '" />' : '<span title="' + title + '">' + category.title + '</span>'
		const li = document.createElement('LI');
		li.className = 'card';
		li.innerHTML = 	'<div>' +
									'<label for="' + id + '">' + caption + '</label>' +
								'</div>';
		parent.appendChild(li);

		const input = document.createElement('INPUT');
		input.type = 'radio'
		input.name = 'channels';
		input.id = id;
		input.value = category.channels.join(' ');

		const channelsList = document.createElement('LI');
		channelsList.innerHTML = '<ul id="channels-' + category.id + '" class="channels"></ul>';

		channelsContainer.appendChild(input);
		channelsContainer.appendChild(channelsList);
	}

	function getMetaDatas() {
		const xhrMetaDatas = new XMLHttpRequest();
		xhrMetaDatas.onreadystatechange = function () {
			if (this.readyState === XMLHttpRequest.DONE) {
				if (this.status === 200) {
					const categories = {};
					const datas = JSON.parse(this.responseText);
					datas.metadata.categories.forEach(function(category) {
						categories[category.id] = {
							id:			category.id,
							title:		category.title,
							channels:	category.channels,
							thumb:		(category.hasOwnProperty('square_art_url')) ? category.square_art_url : null
						};
					});

					datas.metadata.rows.forEach(function(row) {
						const src = (row.hasOwnProperty('web_art_url')) ? 'src="' + ARTS_URL + row.web_art_url + '" ' : '';
						const caption = (src.length > 0) ? row.title : '';
						const id = 'row-' + row.id;
						const oneCategory = (row.hasOwnProperty('category')) ? ' data-category="' + row.category + '"' : '';
						const listId = 'categories-' + row.id;

						const li = document.createElement('LI');
						li.className = 'card';
						li.innerHTML = '<input type="radio" id="' + id + '" name="rows" value="' + row.id + '"' + oneCategory + ' />' +
							'<div>' +
								'<label for="' + id + '"><img ' + src + 'alt="' + row.title + '" title="row #' + row.id + '" style="max-height: 5rem;" /></label>' +
								'<span>' + caption + '</span>' +
							'</div>' +
							'<div class="scrollable">' +
								'<ul id="' + listId + '" class="categories"></ul>' +
							'</div>';
						rowsContainer.appendChild(li);

						const categoriesContainer = document.getElementById(listId);
						if(row.hasOwnProperty('category')) {
							if(!categories.hasOwnProperty(row.category)) {
								console.log('Unkown category with id: ' + row.category);
								return;
							}
							addCategory(categoriesContainer, categories[row.category]);
						} else if(row.hasOwnProperty('categories') && typeof row.categories.forEach == 'function') {
							row.categories.forEach(function(category) {
								if(!categories.hasOwnProperty(category)) {
									console.log('Unkown category with id: ' + category);
									return;
								}
								addCategory(categoriesContainer, categories[category]);
							});
						} else {
							console.log('No category for ' + row.title);
						}
					});
					console.log('Metadatas loaded from ' + API_URL);

					if(channels != null) {
						// all channels are loaded
						rowsContainer.querySelector('li.card:first-of-type label').click();
					} else {
						console.log('Channels are not loaded');
					}
					return;
				}

				console.log('Error #', this.status, this.statusText);
			}
		};

		xhrMetaDatas.open('GET', API_URL + '/metadata.json?locale=' + locale);
		xhrMetaDatas.send();
	}

	rowsContainer.addEventListener('change', function(event) {
		if(event.target.tagName == 'INPUT' && event.target.type == 'radio' && event.target.name == 'rows') {
			document.forms.calmradioChannels.reset();

			const ul = document.getElementById('categories-' + event.target.value);
			ul.parentElement.scrollTo(0 ,0);
			const imgs = ul.querySelectorAll('div:first-of-type img[src=""]');
			if(imgs.length > 0) {
				// lazy loading for <img> tags
				for(var i=0, iMax =imgs.length; i<iMax; i++) {
					imgs[i].src = imgs[i].dataset.src;
				}
			}

			if(event.target.dataset.hasOwnProperty('category')) {
				// Just one channel to display
				const radio = document.getElementById('category-' + event.target.dataset.category);
				if(radio != null) {
					radio.click();
				}
			}
		}
	});

	channelsContainer.addEventListener('change', function(event) {
		if(typeof channels == 'object' && event.target.tagName == 'INPUT' && event.target.type == 'radio' && event.target.name == 'channels') {
			const previous = rowsContainer.querySelectorAll('.categories .card.active');
			if(previous.length > 0) {
				for(var i=0, iMax=previous.length; i<iMax; i++) {
					previous[i].classList.remove('active');
				}
			}

			const parent = event.target.labels[0].parentElement.parentElement;
			parent.classList.add('active');

			const ul = document.getElementById(event.target.id.replace(/^category-/, 'channels-'));
			if(!event.target.hasOwnProperty('channels')) {
				event.target.value.split(/\s+/).forEach(function(channelId) {
					const channel = channels[channelId];
					const streams = new Array();
					var defaultStream = null;
					['free', 'vip'].forEach(function(subscription) {
						if(channel.hasOwnProperty(subscription)) {
							channel[subscription].forEach(function(item) {
								const buf = new Array();
								for(var bitrate in item.streams) {
									const url = item.streams[bitrate];
									buf.push('<a href="' + url + '" data-stream="' + url + '" target="_blank">' + bitrate + 'K</a>');
									if(defaultStream == null) {
										defaultStream = url;
									}
								}
								const title = (subscription == 'vip') ? 'For VIP subscription only' : 'Free access';
								streams.push('<ul class="' + subscription + '" title="' + title + '"><li>' + buf.join('</li><li>') + '</li></ul>');
							});
						}
					});

					const li = document.createElement('LI');
					li.innerHTML = '<div><img src="' + ARTS_URL + channel.square_art_url + '" alt="' + channel.title + '" title="channel #' + channelId + '" data-stream="' + defaultStream + '" /></div>' +
						'<ul class="streams"><li>' + streams.join('</li><li>') + '</li></ul>' +
						'<div>' + channel.description + '</div>';

					ul.appendChild(li);
				});
				event.target.channels = true;
			}

			const scroller = event.currentTarget.parentElement;
			if((typeof window.orientation !== "undefined") || (navigator.userAgent.indexOf('IEMobile') !== -1)) {
				// if mobile then see https://developer.mozilla.org/en-US/docs/Web/API/Element/scrollIntoView
				scroller.scrollIntoView();
			} else {
				// No rotation for a big screen
				scroller.scrollTo(0,0);
				scroller.focus();
			}

		}
	});

	// Reset when reloading the page
	const forms = document.querySelectorAll('#calmradio form');
	if(forms.length > 0) {
		for(var i=0, iMax = forms.length; i<iMax; i++) {
			forms[i].reset();
		}
	}

	getMetaDatas();
	getChannels();
})();
