<?php
# $ipAddr = '192.168.30.77';
$ipAddr = '192.168.58.77';

if($_SERVER['REQUEST_METHOD'] == 'GET' and !empty($_SERVER['QUERY_STRING'])) {
	// https://github.com/karawin/Ka-Radio32/wiki#html-interface-for-the-wifi-webradio
	/*
	 * Possible values for query_STRING in function httpServerHandleConnection() for webserver.c file:
	 * uart, volume=, play=, start, stop, next, prev, instant=, version, infos, list=
	 * */
	// phpinfo(INFO_VARIABLES);
	$ch = curl_init($ipAddr . '?' . $_SERVER['QUERY_STRING']);
	$resp = curl_exec($ch);
	curl_close($ch);
	exit;
}

if(filter_has_var(INPUT_POST, 'action')) {
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
	$action = filter_input(INPUT_POST, 'action', FILTER_SANITIZE_STRING);
	$post_fields = $_POST;
	unset($post_fields['action']);

	// Bug from Ka-Radio
	if(in_array($action, array('play', 'icy', 'soundvol', 'auto'))) {
		$post_fields[''] = '';
	}

	$params = http_build_query($post_fields);
	$ch = curl_init("$ipAddr/$action");
	curl_setopt_array($ch, array(
		CURLOPT_POSTFIELDS => $params,
		CURLOPT_POST => true,
		CURLOPT_RETURNTRANSFER => true
	));
	$resp = curl_exec($ch);
	$curl_infos = curl_getinfo($ch);
	curl_close($ch);
	// error_log(print_r($curl_infos, true), 3, __DIR__ . '/error.log');
	// header('HTTP/1.1 '. $curl_infos['http_code']);
	header('Content-Type: ' . $curl_infos['content_type']);
	header('Content-Length: ' . strlen($resp));
	echo $resp;
	exit;
}

include 'extensions.html';
?>
