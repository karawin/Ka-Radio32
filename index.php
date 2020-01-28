<?php

if(!session_start()) {
	header('Content-Type: text/plain; charset=us-ascii');
	echo 'Session_start() fails';
	exit;
}

if($_SERVER['QUERY_STRING'] === 'bye') {
	session_unset();
	header('Location: index.php');
	exit;
}

if(!array_key_exists('url_device', $_SESSION)) {
	if(filter_has_var(INPUT_POST, 'url_device')) {
		$_SESSION['url_device'] = filter_input(INPUT_POST, 'url_device', FILTER_SANITIZE_STRING);
	} else {
?>
<!DOCTYPE html>
<html lang="fr">
<head>
	<meta http-equiv="X-UA-Compatible" content="IE=Edge" />
	<meta charset="utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1" />
	<title>Ka-Radio32</title>
	<style>
		body { display: flex; justify-content: center; background-color: #444; }
		form { margin-top: 50vh; transform: translateY(-50%); padding: 0.3rem; background-color: #fff; }
		p { margin: 0; }
		p:last-of-type { margin-top: 0.5rem; text-align: center; }
		em { font-size: 80%; }
	</style>
</head><body>
	<form method="post">
		<p>
			<input type="text" name="url_device" placeholder="Domain / IP address for Ka-radio32" required />
			<input type="submit" />
		</p>
		<p><em>
			Click on the right red cross in the next page<br />
			for coming back here.
		</em></p>
	</form>
</body></html>
<?php
		exit;
	}
}

if($_SERVER['REQUEST_METHOD'] == 'GET' and !empty($_SERVER['QUERY_STRING'])) {
	$ch = curl_init($_SESSION['url_device']. '?' . $_SERVER['QUERY_STRING']);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	$resp = curl_exec($ch);
	$curl_infos = curl_getinfo($ch);
	curl_close($ch);
	if($resp !== false) {
		header('Content-Type: ' . $curl_infos['content_type']);
		echo $resp;
	}
	exit;
}

if($_SERVER['REQUEST_METHOD'] == 'POST' and !empty($_SERVER['HTTP_KARADIO_ACTION'])) {
	$params = file_get_contents('php://input');
	$ch = curl_init($_SESSION['url_device'] . '/' . $_SERVER['HTTP_KARADIO_ACTION']);
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

echo preg_replace(
	'#"[^"]+(assets/extensions.css)"#',
	'"$1"',
	strtr(file_get_contents('extensions.html'), array(
		'<body>' => '<body data-ip="' . $_SESSION['url_device'] . '">',
		'<span id="rssi"' => '<a href="?bye" title="for closing the session" style="color: red; text-decoration: none;">&#x2716;</a>' . PHP_EOL . '<span id="rssi"'
	))
);
?>
