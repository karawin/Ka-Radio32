<?php

// See https://somafm.com/channels.json
// https://somafm.com/linktous/
// https://github.com/rockymadden/somafm-cli

const HOSTNAME = 'http://somafm.com';
const TITLE = 'Soma FM';
const ID = 'somafm';
const LOGO = '/img/LogoFP2010.gif';

function innerHTML() {
?>
			<h2>
				<a href="<?= HOSTNAME ?>" target="_blank">
					<img src="<?= HOSTNAME . LOGO ?>" alt="<?= TITLE ?>" />
				</a>
			</h2>
			<div id="<?= ID ?>-channels">
			</div>
<?php
}

function getContainerName() {
	$t = dirname($_SERVER['SCRIPT_NAME']);
	return substr($t, strrpos($t, '/') + 1);
}

function make_body($callback=false) {
	if(is_string($callback)) {
		echo "$callback('" . getContainerName() . "', `";
	}

	innerHTML();

	if(is_string($callback)) {
?>
	</div>
<?php
		$script = (file_exists(__DIR__ . '/script.js')) ? ', 1' : '';
		echo "`$script);";
	}
}

if(!empty($_SERVER)) {
	if(filter_has_var(INPUT_GET, 'innerHTML')) {
		$innerHTML = filter_input(INPUT_GET, 'innerHTML', FILTER_SANITIZE_STRING);
		header('Content-Type: application/javascript; charset=utf-8');
		make_body($innerHTML);
		exit;
	}

?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta http-equiv="X-UA-Compatible" content="IE=Edge" />
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<title>Calm Radio</title>
	<link rel="stylesheet" type="text/css" href="style.css" />
</head>
<body id="<?= ID ?>">
<?php make_body(); ?>
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
