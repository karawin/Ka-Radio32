<?php

const IP_ADDR = '192.168.58.77';

if($_SERVER['REQUEST_METHOD'] == 'GET' and !empty($_SERVER['QUERY_STRING'])) {
	// https://github.com/karawin/Ka-Radio32/wiki#html-interface-for-the-wifi-webradio
	/*
	 * Possible values for query_STRING in function httpServerHandleConnection() for webserver.c file:
	 * uart, volume=, play=, start, stop, next, prev, instant=, version, infos, list=
	 * */
	// phpinfo(INFO_VARIABLES);
	$ch = curl_init(IP_ADDR . '?' . $_SERVER['QUERY_STRING']);
	$resp = curl_exec($ch);
	curl_close($ch);
	exit;
}

if($_SERVER['REQUEST_METHOD'] == 'POST') {
	/*
	 * Fields for POST request :
		$params = array(
			'auto'			=> false,
			'clear'			=> false,
			'getStation'	=> array('idgp'),
			'hardware'		=> false,
			'icy'			=> array(),
			'instant_play'	=> array('url', 'port', 'path'),
			'play'			=> array('id'),
			'rauto'			=> false,
			'setStation'	=> array('nb', 'id', 'url', 'name', 'file', 'ovol', 'port'),
			'sound'			=> array('bass', 'treble', 'bassfreq', 'treblefreq', 'spacial'),
			'soundvol'		=> array('vol'),
			'stop'			=> false,
			'upgrade'		=> false,
			'wifi'			=> array(
				'valid', // For reboot
				'ssid', 'pasw',
				'ssid2', 'pasw2',
				'dhcp', 'dhcp2',
				'ip', 'msk', 'gw',
				'ip2', 'msk2', 'gw2',
				'ua',
				'host',
				'tzo'
			)
		);
	 * */

	if(empty($_SERVER['HTTP_KARADIO_ACTION'])) { exit; }

	$params = file_get_contents('php://input');
	$ch = curl_init(IP_ADDR . '/' . $_SERVER['HTTP_KARADIO_ACTION']);
	curl_setopt_array($ch, array(
		CURLOPT_POSTFIELDS => $params,
		CURLOPT_POST => true,
		CURLOPT_RETURNTRANSFER => true
	));
	$resp = curl_exec($ch);
	$curl_infos = curl_getinfo($ch);
	curl_close($ch);
	header('Content-Type: ' . $curl_infos['content_type']);
	header('Content-Length: ' . strlen($resp));
	echo $resp;
	exit;
}

echo str_replace('<body>', '<body data-ip="' . IP_ADDR . '">', file_get_contents('extensions.html'));
?>
