<?php
const URL = 'https://www.1.fm/mainstations';
const FILENAME = __DIR__ .'/1-fm.json';
const MAX_RETENTION = 3600 * 8; // eight hours

if(!file_exists(FILENAME) or time() - filemtime(FILENAME) > MAX_RETENTION) {
	$fn = fopen(FILENAME, 'w');
	$ch = curl_init(URL);
	curl_setopt_array($ch, array(
		CURLOPT_FOLLOWLOCATION	=> true,
		CURLOPT_FILE			=> $fn
	));
	curl_exec($ch);
	curl_close($ch);
	fclose($fn);
}

$content = file_get_contents(FILENAME);
$stations = json_decode($content, true);

const SEP1 = <<< SEP
</option>
		<option>
SEP;
const SEP2 = <<< SEP2
</span>
					<span class="related">
SEP2;

function genres_print() {
	global $stations;

	$genres = array();
	foreach($stations as $st) {
		if($st['active']) {
			foreach(explode(',', $st['relatedstations']) as $item) {
				if(!array_key_exists($item, $genres)) {
					$genres[$item] = 1;
				} else {
					$genres[$item]++;
				}
			}
		}
	}
	arsort($genres);
	echo <<< BEGIN
	<select id="related">
		<option value="">All</option>\n
		<option>
BEGIN;
	echo implode(SEP1, array_keys($genres));
	echo <<< END
		</option>
	</select>
END;
}

function stations_list_print() {
	global $stations;

	uasort($stations, function($a, $b) {
		return strnatcasecmp($a['name'], $b['name']);
	});
	$genres = array();
	foreach($stations as $st) {
		if($st['active']) {
			$relateds = preg_replace('@\s*,\s*@', SEP2, $st['relatedstations']);
			$title = preg_replace('@\s*radio$@i', '', $st['name']);
			echo <<< STATION
			<div data-id="${st['id']}" data-related="${st['relatedstations']}">
				<div data-stream="${st['strm128kmp3']}" data-mp3="${st['128kmp3']}">
					<div class="bg-${st['id']}"></div>
					<svg class="icon">
						<use xlink:href="symbols.svg#icon-${st['id']}" />
					</svg>
				</div>
				<h2 title="${st['id']}">$title</h2>
				<div class="desc">${st['long_desc']}</div>
				<div class="genre">
					<span class="related">$relateds</span>
				</div>
			</div>\n
STATION;
		}
	}
}

if(filter_has_var(INPUT_SERVER, 'HTTP_REFERER')) {
	$url = parse_url(filter_input(INPUT_SERVER, 'HTTP_REFERER', FILTER_SANITIZE_STRING));
	if($url['host'] == $_SERVER['HTTP_HOST'] /* and $url['path'] == */) {
		exit;
	}
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta http-equiv="X-UA-Compatible" content="IE=Edge" />
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<link rel="stylesheet" type="text/css" href="backgrounds.css" />
	<link rel="stylesheet" type="text/css" href="1-fm.css" />
	<title>1.FM</title>
</head><body>
	<nav>
<?php genres_print(); ?>
	</nav>
	<section id="main">
<?php stations_list_print(); ?>
	</section>
	<footer>
	</footer>
	<script>
		(function() {
			'use strict';

			const select1 = document.getElementById('related');

			function extractFullUrl(fullUrl) {
				const matches = /(?:https?:\/\/)([^:/]*)(?::(\d{2,5}))?(\/.*)?$/.exec(fullUrl);
				return (matches == null) ? null : {
					url:	matches[1],
					port:	(typeof matches[2] === 'string' ) ? matches[2] : '80',
					path1:	(typeof matches[3] === 'string' ) ? matches[3] : '/'
				}
			}

			const xhr = new XMLHttpRequest();
			xhr.instantPlay = function(fullUrl) {
				let datas = extractFullUrl(fullUrl);
				if(datas != null) {
					this.open('POST', '../../proxy.php?action=instant_play');
					this.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
					this.send('url=' + datas.url + '&port=' + datas.port + '&path=' + encodeURI(datas.path1));
				}
			}

			function relatedStations(value) {
				let pattern = new RegExp('\\b' + value + '\\b');
				let stations = document.querySelectorAll('#main div[data-related]');
				for(let i=0, iMax=stations.length; i<iMax; i++) {
					if(pattern.test(stations[i].dataset.related)) {
						stations[i].classList.remove('hidden');
					} else {
						stations[i].classList.add('hidden');
					}
				}
			}

			document.getElementById('main').addEventListener('click', function(event) {
				let el = event.target;
				if(el.tagName == 'use') {
					el = el.parentElement;
				}
				if(el.tagName == 'svg' || el.className.startsWith('bg-')) {
					el = el.parentElement;
				}
				if(el.hasAttribute('data-stream')) {
					event.preventDefault();
					xhr.instantPlay('http://' + el.dataset.stream);
					return;
				}

				if(el.tagName == 'SPAN' && el.classList.contains('related')) {
					event.preventDefault();
					select1.value = el.textContent;
					relatedStations(el.textContent);
				}
			});

			select1.addEventListener('change', function(event) {
				event.preventDefault();
				relatedStations(this.value);
			});
		})();
	</script>
</body></html>
