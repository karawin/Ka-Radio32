(function() {
	'use strict';

	const HOSTNAME = 'http://somafm.com/';
	const API_URL = 'https://api.somafm.com/channels.json';
	const container = document.getElementById('somafm-channels');

	const xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() {
		if (this.readyState === XMLHttpRequest.DONE) {
			if(this.status === 200) {
				const datas = JSON.parse(this.responseText);
				console.log(datas.channels.length + ' channels from ' + API_URL);
				datas.channels.forEach(function(item) {
					var stream = null;
					for(var i=0, iMax=item.playlists.length; i<iMax; i++) {
						if(item.playlists[i].format == 'mp3') {
							stream = item.playlists[i].url;
							break;
						}
					}
					const figure = document.createElement('FIGURE');
					figure.innerHTML = '<figcaption><a href="' + HOSTNAME + item.id + '/" target=_blank>' + item.title + '</a></figcaption>' +
						'<p><em>' + item.listeners + ' listeners</em></p>' +
						// '<img src="' + item.image + '" data-stream="' + stream + '" />' +
						'<img src="' + item.image + '" data-streams="' + stream + '" />' +
						'<p>' + item.description + '</p>';
					container.appendChild(figure);
				});

				/*
				 * Hack against Ka-Radio.
				 * Doesn't parse right pls file. E.G : https://api.somafm.com/bagel.pls.
				 * When fixed replace above "data-streams" by "data-stream" and drop the following listener
				 * */
				container.addEventListener('click', function(event) {
					if('streams' in event.target.dataset) {
						event.preventDefault();
						const xhr = new XMLHttpRequest();
						xhr.onreadystatechange = function() {
							if (this.readyState === XMLHttpRequest.DONE) {
								if(this.status === 200) {
									const matches = this.responseText.match(/^File\d+=(.*)$/m);
									if(matches != null) {
										instantPlayForm.elements.fullUrl.value = matches[1];
										instantPlayForm.elements.instantPlayBtn.click();
									} else {
										console.log('pls file format not valid');
									}
								} else {
									console.log('somafm error code ' + this.status, this.statusText);
								}
							}
						};
						xhr.open('GET', event.target.dataset.streams);
						xhr.send();
					}
				});

				return;
			}

			console.log('somafm error code ' + this.status, this.statusText);
		}
	};
	xhr.open('GET', API_URL);
	xhr.send();
})();
