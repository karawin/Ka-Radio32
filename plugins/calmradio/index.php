<?php

const HOSTNAME = 'http://calmradio.com';
const TITLE = 'Calm Radio';
const ID = 'calmradio';
const LOGO = '/templates/calmradio/images/logo-dark.svg';

/*
 * https://api.calmradio.com/v2/channels.json?locale=en
 * https://api.calmradio.com/v2/metadata.json?locale=en
 * https://arts.calmradio.com
 * */

function getContainerName() {
	$t = dirname($_SERVER['SCRIPT_NAME']);
	return substr($t, strrpos($t, '/') + 1);
}

function make_body($locale, $callback=false) {
	if(is_string($callback)) {
		echo "$callback('" . getContainerName() . "', `";
	}
?>
	<h2>
		<a href="<?= HOSTNAME ?>" target="_blank">
			<img src="<?= HOSTNAME . LOGO ?>" alt="<?= TITLE ?>" style="max-height: 5rem;" />
		</a>
	</h2>
	<div>
	<form>
		<div class="scrollable">
			<ul id="calmradio-metadata" class="main rows"></ul>
		</div>
	</form>
	<form name="calmradioChannels">
		<div class="scrollable">
			<ul id="calmradio-channels"></ul>
		</div>
	</form>
	</div>
<?php
	if(is_string($callback)) {
		$script = (file_exists(__DIR__ . '/script.js')) ? ', 1' : '';
		echo "`$script);";
	}
}

if(!empty($_SERVER)) {
	if(filter_has_var(INPUT_GET, 'callback')) {
		$callback = filter_input(INPUT_GET, 'callback', FILTER_SANITIZE_STRING);
		$output = $callback . '(`' . $datas . '`);';
		header('Content-Type: application/javascript; charset=utf-8');
		header('Content-Length: ' . strlen($output));
		echo $output;
		exit;
	}

	if(filter_has_var(INPUT_GET, 'innerHTML')) {
		$innerHTML = filter_input(INPUT_GET, 'innerHTML', FILTER_SANITIZE_STRING);
		header('Content-Type: application/javascript; charset=utf-8');
		make_body($locale, $innerHTML);
		exit;
	}

?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta http-equiv="X-UA-Compatible" content="IE=Edge" />
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<title><?= TITLE ?></title>
	<link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body id="calmradio">
<?php make_body($locale); ?>
<?php
	if(empty($callback) and file_exists(__DIR__ . '/script.js')) {
?>
	<script type="text/javascript" src="script.js"></script>
<?php
	}
?>
</body></html>
<?php
	exit;
}

?>
