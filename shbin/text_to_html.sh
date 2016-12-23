#!/bin/sh

FILE=$1


	printf '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"> <pre>\n' > ${FILE}.html
	cat $FILE >> ${FILE}.html
	printf '</pre>\n' >>  ${FILE}.html
	sed -i 's/\(http.*\)/<a href="&">&<\/a>/g'  ${FILE}.html
	sed -i 's/\([a-Z,0-9,.,-]*@.*\)/<a href="mailto:&">&<\/a>/g'  ${FILE}.html
	sed -i '2s/\(^[^\t][a-Z].*\)/<br clear="left"\/><\/pre><dl><strong>&<\/strong><\/dl><pre>/'  ${FILE}.html
	sed -i 's/\(^[^\t][a-Z].*\)/<br clear="left"\/><\/pre><dl>&<\/dl><pre>/g'  ${FILE}.html
	sed -i 's/\(^[^\t]-.*\)/<\/pre><dd><hr\/><\/dd><pre>/g' ${FILE}.html
	sed -i 's/\([a-Z,0-9,\/,.,-]*.png\)/<\/pre><dl><img src="&" style="float:left;height:15em;margin-right:1em"><\/img><pre><\/dl>/g' ${FILE}.html



