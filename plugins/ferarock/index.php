<?php
const HOSTNAME = 'http://ferarock.org';
const FILENAME = __DIR__ . '/ferarock.json';
const TITLE = 'Ferarock';
const ID = 'ferarock';
const LOGO = '/sites/all/themes/t_ferarock/img/website-logo.png';

const PATTERN1 = '/les-radios';
const PATTERN2 = '#^.*?https?://[^/]*([^\?]*).*#s';

if(!file_exists(FILENAME) or time() - filemtime(FILENAME) > 28800) { # 8 hours
	$ch = curl_init(HOSTNAME . '/les-radios');
	curl_setopt_array($ch, array(
		CURLOPT_RETURNTRANSFER	=> true,
		CURLOPT_FOLLOWLOCATION	=> true,
		CURLOPT_FORBID_REUSE	=> true,
		CURLOPT_HEADER			=> false
	));

	$content = curl_exec($ch);
	if(!is_string($content)) {
		header('Content-Type: text/plain');
		echo 'No data' . PHP_EOL . PHP_EOL;
		exit;
	}

	$channels = array();
	$dom = new DOMDocument();
	@$dom->loadHTML($content);
	$xpath = new DOMXPath($dom);
	$queries = array(
		'title'		=> '//*/h1[@class="node-titre"]',
		'subTitle'	=> '//*/h2[@class="node-radio-sous-titre"]',
		'thumb'		=> '//*/img[@class="lazyload"]',
		'streams'	=> '//*/noscript/*/a',
		'descr'		=> '//*/div[@id="node-texte"]',
		'url'		=> '//*/div[@id="node-texte"]//a[starts-with(@href,"http")]'
	);
	foreach($xpath->query('//*/div[@id="afficher_plusliste_3"]/*/a[starts-with(@href,"' . PATTERN1 . '")]') as $node) {
		$link = $node->getAttribute('href');
		curl_setopt($ch, CURLOPT_URL, HOSTNAME . $link);
		$stationContent = curl_exec($ch);
		if(is_string($stationContent)) {
			$buffer = array();
			$stationDom = new DOMDocument();
			@$stationDom->loadHTML($stationContent);
			$stationXPath = new DOMXPath($stationDom);
			$articles = $stationXPath->query('//*/article[@id="node"]');
			foreach($queries as $k=>$q) {
				$nodes = $stationXPath->query($q, $articles[0]);
				if($nodes->length > 0) {
					$n = $nodes[0];
					switch($k) {
						case 'thumb' :
							$attr = ($n->hasAttribute('data-srcset')) ? 'data-srcset' : 'src';
							$buffer[$k] = preg_replace(PATTERN2, '$1', $n->getAttribute($attr));
							break;
						case 'streams' :
							$buffer[$k] = $n->getAttribute('href');
							break;
						case 'url' :
							foreach($nodes as $anchor) {
								if(preg_match('#internet#i', $anchor->textContent)) {
									$buffer[$k] = $anchor->getAttribute('href');
									break;
								}
							}
							break;
						case 'descr' :
							foreach($n->childNodes as $child) {
								if(in_array($child->nodeName, array('p', 'div'))) {
									$value = trim($child->textContent);
									if(!empty($value) and preg_match('#^\w#', $value)) {
										$buffer[$k] = $value;
										break;
									}
								}
							}
							break;
						default:
							$buffer[$k] = trim($n->textContent);
					}
				}
			}
			$channels[trim(substr($link, strlen(PATTERN1)), " \t\n\r\0\x0B\\/")] = $buffer;
		}
	}

	$response = array(
		'id'		=> ID,
		'hostname'	=> HOSTNAME,
		'title'		=> TITLE,
		'logo'		=> LOGO,
		'channels'	=> $channels
	);

	$datas = json_encode($response, JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES | JSON_PRETTY_PRINT);
	if(is_writable(__DIR__)) {
		file_put_contents(FILENAME, $datas);
	}
} else {
	$datas = file_get_contents(FILENAME);
}

function getContainerName() {
	$t = dirname($_SERVER['SCRIPT_NAME']);
	return substr($t, strrpos($t, '/') + 1);
}

if(!empty($_SERVER)) {
	if(filter_has_var(INPUT_GET, 'callback')) {
		$callback = filter_input(INPUT_GET, 'callback', FILTER_SANITIZE_STRING);
		$output = $callback . '(`' . $datas . '`);';
		header('Content-Type: application/javascript; charset=utf-8');
		header('Content-Length: ' . strlen($output));
		echo $output;
	} elseif(filter_has_var(INPUT_GET, 'innerHTML')) {
		$innerHTML = filter_input(INPUT_GET, 'innerHTML', FILTER_SANITIZE_STRING);
		$container = getContainerName();
		$response = json_decode($datas, true);
		$channels = array();
		foreach($response['channels'] as $id=>$params) {
			$channels[] = <<< CHANNEL
		<figure>
			<figcaption><a href="${params['url']}" target=_blank>${params['title']}</a></figcaption>
			<img src="${response['hostname']}${params['thumb']}" data-stream="${params['streams']}" />
			<div>${params['subTitle']}</div>
			<p>${params['descr']}</p>
		</figure>
CHANNEL;
		}
		$buf = implode(PHP_EOL, $channels);
		$output = <<< OUTPUT
	$innerHTML('$container', `<div id="${response['id']}">
			<h2>
				<a href="${response['hostname']}" target="_blank">
					<img src="${response['hostname']}${response['logo']}" alt="${response['title']}" />
				</a>
			</h2>
			<div id="${response['id']}-channels">
				$buf
			</div>
		</div>`);
OUTPUT;
		header('Content-Type: application/javascript; charset=utf-8');
		header('Content-Length: ' . strlen($output));
		echo $output;
	} else {
		header('Content-Type: application/json; charset=utf-8');
		header('Content-Length: ' . strlen($datas));
		echo $datas;
	}
	exit;
}

echo $datas;
echo PHP_EOL;
?>
