all: 1900-neitzsche.htm 1901-20thcent.htm 1903-siberian.htm 1918-ch02.htm entities.dat

1900-neitzsche.htm:
	wget https://www.marxists.org/archive/trotsky/1900/12/nietzsche.htm -O 1900-neitzsche.htm

1901-20thcent.htm:
	wget https://www.marxists.org/archive/trotsky/1901/xx/20thcent.htm -O 1901-20thcent.htm

1903-siberian.htm:
	wget https://www.marxists.org/archive/trotsky/1903/xx/siberian.htm -O 1903-siberian.htm

1918-ch02.htm:
	wget https://www.marxists.org/archive/trotsky/1918/ourrevo/ch02.htm -O 1918-ch02.htm

entities.dat:
	html2text -ascii ./*.htm | grep -o "\&\#[0-9]\+;" | sort | uniq > entities.dat
