#!/bin/sh

# TEST COMPLETO: Práctica de todos los comandos test
# Basado en el Tema 9 de Shell Scripting

echo "=========================================="
echo "PRACTICUM: COMANDO TEST EN #!/bin/sh"
echo "=========================================="

# ==================================================
# PARTE 1: TEST CON FICHEROS
# ==================================================

echo ""
echo "=== PARTE 1: TEST CON FICHEROS ==="
echo ""

# Crear ficheros de prueba
touch /tmp/fichero_existe.txt
mkdir -p /tmp/directorio_existe

# test -f: ¿Fichero regular existe?
echo "1. test -f /tmp/fichero_existe.txt (debe existir)"
if test -f /tmp/fichero_existe.txt
then
    echo "   ✓ VERDADERO: Fichero existe"
else
    echo "   ✗ FALSO: Fichero no existe"
fi

echo ""
echo "2. test -f /tmp/no_existe.txt (NO debe existir)"
if test -f /tmp/no_existe.txt
then
    echo "   ✓ VERDADERO: Fichero existe"
else
    echo "   ✗ FALSO: Fichero no existe"
fi

# test -d: ¿Directorio existe?
echo ""
echo "3. test -d /tmp/directorio_existe (debe ser directorio)"
if test -d /tmp/directorio_existe
then
    echo "   ✓ VERDADERO: Es un directorio"
else
    echo "   ✗ FALSO: No es un directorio"
fi

echo ""
echo "4. test -d /tmp/fichero_existe.txt (NO es directorio)"
if test -d /tmp/fichero_existe.txt
then
    echo "   ✓ VERDADERO: Es un directorio"
else
    echo "   ✗ FALSO: No es un directorio"
fi

# Diferencia: -f con un directorio
echo ""
echo "5. test -f /tmp/directorio_existe (fichero REGULAR, no directorio)"
if test -f /tmp/directorio_existe
then
    echo "   ✓ VERDADERO: Es fichero regular"
else
    echo "   ✗ FALSO: NO es fichero regular"
fi

# test -e: ¿Existe (fichero o directorio)?
echo ""
echo "6. test -e /tmp/fichero_existe.txt (debe existir algo)"
if test -e /tmp/fichero_existe.txt
then
    echo "   ✓ VERDADERO: Existe (fichero)"
else
    echo "   ✗ FALSO: No existe"
fi

echo ""
echo "7. test -e /tmp/directorio_existe (debe existir algo)"
if test -e /tmp/directorio_existe
then
    echo "   ✓ VERDADERO: Existe (directorio)"
else
    echo "   ✗ FALSO: No existe"
fi

# test -s: ¿Fichero existe Y tiene tamaño > 0?
echo ""
echo "8. test -s /tmp/fichero_existe.txt (fichero vacío)"
if test -s /tmp/fichero_existe.txt
then
    echo "   ✓ VERDADERO: Fichero tiene contenido"
else
    echo "   ✗ FALSO: Fichero vacío o no existe"
fi

echo "Agregando contenido al fichero..."
echo "contenido" > /tmp/fichero_existe.txt

echo ""
echo "9. test -s /tmp/fichero_existe.txt (fichero con contenido)"
if test -s /tmp/fichero_existe.txt
then
    echo "   ✓ VERDADERO: Fichero tiene contenido"
else
    echo "   ✗ FALSO: Fichero vacío o no existe"
fi

# ==================================================
# PARTE 2: TEST CON CADENAS
# ==================================================

echo ""
echo "=== PARTE 2: TEST CON CADENAS ==="
echo ""

# test -z: ¿Cadena vacía?
cadena_vacia=""
cadena_llena="hola"

echo "10. test -z \"\" (cadena VACÍA)"
if test -z "$cadena_vacia"
then
    echo "   ✓ VERDADERO: Cadena está vacía"
else
    echo "   ✗ FALSO: Cadena no está vacía"
fi

echo ""
echo "11. test -z \"hola\" (cadena CON CONTENIDO)"
if test -z "$cadena_llena"
then
    echo "   ✓ VERDADERO: Cadena está vacía"
else
    echo "   ✗ FALSO: Cadena no está vacía"
fi

# test -n: ¿Cadena no vacía?
echo ""
echo "12. test -n \"\" (cadena VACÍA)"
if test -n "$cadena_vacia"
then
    echo "   ✓ VERDADERO: Cadena no está vacía"
else
    echo "   ✗ FALSO: Cadena está vacía"
fi

echo ""
echo "13. test -n \"hola\" (cadena CON CONTENIDO)"
if test -n "$cadena_llena"
then
    echo "   ✓ VERDADERO: Cadena no está vacía"
else
    echo "   ✗ FALSO: Cadena está vacía"
fi

# test sin -n: ¿Cadena no nula? (equivalente a -n)
echo ""
echo "14. [ \"\$cadena_llena\" ] (cadena CON CONTENIDO)"
if [ "$cadena_llena" ]
then
    echo "   ✓ VERDADERO: Cadena no nula"
else
    echo "   ✗ FALSO: Cadena es nula"
fi

# Igualdad de cadenas: =
echo ""
echo "15. test \"hola\" = \"hola\" (IGUALES)"
if test "hola" = "hola"
then
    echo "   ✓ VERDADERO: Cadenas son iguales"
else
    echo "   ✗ FALSO: Cadenas son diferentes"
fi

echo ""
echo "16. test \"hola\" = \"mundo\" (DIFERENTES)"
if test "hola" = "mundo"
then
    echo "   ✓ VERDADERO: Cadenas son iguales"
else
    echo "   ✗ FALSO: Cadenas son diferentes"
fi

# Desigualdad de cadenas: !=
echo ""
echo "17. test \"hola\" != \"mundo\" (NO IGUALES)"
if test "hola" != "mundo"
then
    echo "   ✓ VERDADERO: Cadenas NO son iguales"
else
    echo "   ✗ FALSO: Cadenas son iguales"
fi

echo ""
echo "18. test \"hola\" != \"hola\" (SON IGUALES)"
if test "hola" != "hola"
then
    echo "   ✓ VERDADERO: Cadenas NO son iguales"
else
    echo "   ✗ FALSO: Cadenas son iguales"
fi

# Comparación con variables
nombre="Juan"
echo ""
echo "19. Comparar variable: nombre=$nombre"
if test "$nombre" = "Juan"
then
    echo "   ✓ VERDADERO: La variable contiene 'Juan'"
else
    echo "   ✗ FALSO: La variable no contiene 'Juan'"
fi

# ==================================================
# PARTE 3: TEST CON NÚMEROS
# ==================================================

echo ""
echo "=== PARTE 3: TEST CON NÚMEROS ==="
echo ""

a=10
b=20
c=10

# -eq: ¿Iguales?
echo "20. test $a -eq $c (10 -eq 10, IGUALES)"
if test $a -eq $c
then
    echo "   ✓ VERDADERO: Son iguales"
else
    echo "   ✗ FALSO: No son iguales"
fi

echo ""
echo "21. test $a -eq $b (10 -eq 20, DIFERENTES)"
if test $a -eq $b
then
    echo "   ✓ VERDADERO: Son iguales"
else
    echo "   ✗ FALSO: No son iguales"
fi

# -ne: ¿No iguales?
echo ""
echo "22. test $a -ne $b (10 -ne 20, DISTINTOS)"
if test $a -ne $b
then
    echo "   ✓ VERDADERO: No son iguales"
else
    echo "   ✗ FALSO: Son iguales"
fi

echo ""
echo "23. test $a -ne $c (10 -ne 10, IGUALES)"
if test $a -ne $c
then
    echo "   ✓ VERDADERO: No son iguales"
else
    echo "   ✗ FALSO: Son iguales"
fi

# -gt: ¿Mayor que?
echo ""
echo "24. test $a -gt $b (10 -gt 20, 10 NO es mayor que 20)"
if test $a -gt $b
then
    echo "   ✓ VERDADERO: 10 es mayor que 20"
else
    echo "   ✗ FALSO: 10 NO es mayor que 20"
fi

echo ""
echo "25. test $b -gt $a (20 -gt 10, 20 SÍ es mayor que 10)"
if test $b -gt $a
then
    echo "   ✓ VERDADERO: 20 es mayor que 10"
else
    echo "   ✗ FALSO: 20 NO es mayor que 10"
fi

# -ge: ¿Mayor o igual?
echo ""
echo "26. test $a -ge $c (10 -ge 10, IGUALES)"
if test $a -ge $c
then
    echo "   ✓ VERDADERO: 10 >= 10"
else
    echo "   ✗ FALSO: 10 NO >= 10"
fi

echo ""
echo "27. test $a -ge $b (10 -ge 20, 10 NO >= 20)"
if test $a -ge $b
then
    echo "   ✓ VERDADERO: 10 >= 20"
else
    echo "   ✗ FALSO: 10 NO >= 20"
fi

# -lt: ¿Menor que?
echo ""
echo "28. test $a -lt $b (10 -lt 20, SÍ es menor)"
if test $a -lt $b
then
    echo "   ✓ VERDADERO: 10 es menor que 20"
else
    echo "   ✗ FALSO: 10 NO es menor que 20"
fi

echo ""
echo "29. test $b -lt $a (20 -lt 10, NO es menor)"
if test $b -lt $a
then
    echo "   ✓ VERDADERO: 20 es menor que 10"
else
    echo "   ✗ FALSO: 20 NO es menor que 10"
fi

# -le: ¿Menor o igual?
echo ""
echo "30. test $a -le $c (10 -le 10, IGUALES)"
if test $a -le $c
then
    echo "   ✓ VERDADERO: 10 <= 10"
else
    echo "   ✗ FALSO: 10 NO <= 10"
fi

echo ""
echo "31. test $b -le $a (20 -le 10, 20 NO <= 10)"
if test $b -le $a
then
    echo "   ✓ VERDADERO: 20 <= 10"
else
    echo "   ✗ FALSO: 20 NO <= 10"
fi

# ==================================================
# PARTE 4: TEST CON ARGUMENTOS ($#)
# ==================================================

echo ""
echo "=== PARTE 4: TEST CON ARGUMENTOS ==="
echo ""

echo "Este script fue llamado CON argumentos"
echo "Número de argumentos: $#"

echo ""
echo "32. test \$# -eq 0 (¿Tiene 0 argumentos?)"
if test $# -eq 0
then
    echo "   ✓ VERDADERO: Sin argumentos"
else
    echo "   ✗ FALSO: Tiene argumentos"
fi

echo ""
echo "33. test \$# -ne 0 (¿Tiene argumentos?)"
if test $# -ne 0
then
    echo "   ✓ VERDADERO: Tiene argumentos"
else
    echo "   ✗ FALSO: Sin argumentos"
fi

echo ""
echo "34. test \$# -gt 0 (¿Más de 0 argumentos?)"
if test $# -gt 0
then
    echo "   ✓ VERDADERO: Tiene más de 0 argumentos"
else
    echo "   ✗ FALSO: Tiene 0 argumentos"
fi

# ==================================================
# PARTE 5: SINTAXIS ALTERNATIVA [ ... ]
# ==================================================

echo ""
echo "=== PARTE 5: SINTAXIS ALTERNATIVA [ ... ] ==="
echo ""

echo "Las siguientes sintaxis son equivalentes:"
echo ""
echo "35. test -f /tmp/fichero_existe.txt"
if test -f /tmp/fichero_existe.txt
then
    echo "   ✓ Funciona"
fi

echo ""
echo "36. [ -f /tmp/fichero_existe.txt ]"
if [ -f /tmp/fichero_existe.txt ]
then
    echo "   ✓ Funciona"
fi

echo ""
echo "37. test \"hola\" = \"hola\""
if test "hola" = "hola"
then
    echo "   ✓ Funciona"
fi

echo ""
echo "38. [ \"hola\" = \"hola\" ]"
if [ "hola" = "hola" ]
then
    echo "   ✓ Funciona"
fi

# ==================================================
# PARTE 6: NEGACIÓN CON !
# ==================================================

echo ""
echo "=== PARTE 6: NEGACIÓN CON ! ==="
echo ""

echo "39. ! test -f /tmp/no_existe.txt (negación: NO existe)"
if ! test -f /tmp/no_existe.txt
then
    echo "   ✓ VERDADERO: Fichero NO existe"
else
    echo "   ✗ FALSO: Fichero existe"
fi

echo ""
echo "40. ! test -f /tmp/fichero_existe.txt (negación: SÍ existe)"
if ! test -f /tmp/fichero_existe.txt
then
    echo "   ✓ VERDADERO: Fichero NO existe"
else
    echo "   ✗ FALSO: Fichero existe"
fi

# ==================================================
# PARTE 7: OPERADORES LÓGICOS (AND, OR)
# ==================================================

echo ""
echo "=== PARTE 7: OPERADORES LÓGICOS ==="
echo ""

echo "41. Operador AND (&&): condición1 && condición2"
if test -f /tmp/fichero_existe.txt && test -n "contenido"
then
    echo "   ✓ VERDADERO: Ambas condiciones se cumplen"
else
    echo "   ✗ FALSO: Alguna condición falla"
fi

echo ""
echo "42. Operador OR (||): condición1 || condición2"
if test -f /tmp/no_existe.txt || test -d /tmp/directorio_existe
then
    echo "   ✓ VERDADERO: Al menos una condición se cumple"
else
    echo "   ✗ FALSO: Ninguna condición se cumple"
fi

# ==================================================
# LIMPIEZA
# ==================================================

echo ""
echo "=== LIMPIEZA ==="
rm -f /tmp/fichero_existe.txt
rm -rf /tmp/directorio_existe
echo "Ficheros de prueba eliminados"

# ==================================================
# RESUMEN
# ==================================================

echo ""
echo "=========================================="
echo "RESUMEN DE OPERADORES TEST"
echo "=========================================="
echo ""
echo "FICHEROS:"
echo "  -f fichero    → ¿Es fichero regular?"
echo "  -d fichero    → ¿Es directorio?"
echo "  -e fichero    → ¿Existe (fichero o directorio)?"
echo "  -s fichero    → ¿Fichero existe y tamaño > 0?"
echo ""
echo "CADENAS:"
echo "  -z cadena     → ¿Cadena vacía?"
echo "  -n cadena     → ¿Cadena no vacía?"
echo "  cadena        → ¿Cadena no nula? (igual a -n)"
echo "  cad1 = cad2   → ¿Iguales?"
echo "  cad1 != cad2  → ¿Diferentes?"
echo ""
echo "NÚMEROS:"
echo "  num1 -eq num2 → ¿Iguales?"
echo "  num1 -ne num2 → ¿Diferentes?"
echo "  num1 -gt num2 → ¿Mayor que?"
echo "  num1 -ge num2 → ¿Mayor o igual?"
echo "  num1 -lt num2 → ¿Menor que?"
echo "  num1 -le num2 → ¿Menor o igual?"
echo ""
echo "LÓGICA:"
echo "  ! condición   → Negación"
echo "  cond && cond  → AND"
echo "  cond || cond  → OR"
echo ""
echo "SINTAXIS:"
echo "  test condición"
echo "  [ condición ]"
echo ""
echo "=========================================="
echo "FIN DEL PRACTICUM"
echo "=========================================="

exit 0
