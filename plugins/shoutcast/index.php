<?php

const HOSTNAME = 'https://www.shoutcast.com';
const TITLE = 'Shoutcast';
const ID = 'shoutcast';
const LOGO = 'http://wiki.shoutcast.com/images/6/61/Logo_shoutcast.png';

function innerHTML() {
?>
<div>
	<div>
		<div>
			<a id="sh-link" href="<?= HOSTNAME ?>" target="_blank"><img src="<?= LOGO ?>" alt="<?= TITLE ?> logo"/></a>
		</div>
		<h2 id="sh-title">Genre</h2>
		<ul id="sh-genrelist-0">
			<li>
				<input id="sh-genre-top500" name="sh-radio-genre-0" type="radio" value="-1" />
				<label for="sh-genre-top500">Top 500</label>
			</li>
		</ul>
		<form name="sh_search">
			<input type="text" name="query" placeholder="Now playing..." required />
			<input type="submit" value="Search" />
		</form>
	</div>
	<div>
		<div id="sh-playlist"></div>
		<div class="loader">Loading</div>
	</div>
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
