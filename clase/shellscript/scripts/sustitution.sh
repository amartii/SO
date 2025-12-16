#!/bin/sh
fecha=$(date)
echo "Sin $: echo fecha"
echo fecha

echo ""
echo "Con $: echo \$fecha"
echo $fecha

echo ""
echo "Con \$ y comillas: echo \"\$fecha\""
echo "$fecha"

exit 0
