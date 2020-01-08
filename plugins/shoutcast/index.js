kaPlugin('shoutcast', `<div>
	<div>
		<div>
			<a id="sh-link" href="https://www.shoutcast.com" target="_blank"><img src="http://wiki.shoutcast.com/images/6/61/Logo_shoutcast.png" alt="Shoutcast logo"/></a>
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
	</div>
`, 1);