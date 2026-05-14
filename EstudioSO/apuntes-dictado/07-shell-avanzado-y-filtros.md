# Tema 7: Shell Avanzado, Filtros y Expresiones Regulares

Este tema cubre las herramientas de filtrado de texto de Unix, que son extremadamente potentes. Te permiten procesar ficheros de texto de forma eficiente usando la filosofia Unix: cada herramienta hace una cosa bien, y se combinan con pipes.

## Expresiones regulares

Las expresiones regulares son patrones para buscar texto. Los metacaracteres basicos son: el punto, que coincide con cualquier caracter; el asterisco, que significa cero o mas repeticiones del caracter anterior; el acento circunflejo, que significa inicio de linea; y el signo dolar, que significa fin de linea. Los corchetes definen clases de caracteres: a, e, i, o, u coincide con cualquier vocal. El guion dentro de los corchetes define rangos: cero menos nueve coincide con cualquier digito. El acento circunflejo dentro de los corchetes niega: circunflejo cero menos nueve coincide con cualquier cosa que no sea un digito.

En expresiones regulares extendidas, que se usan con egrep, tenemos ademas: el mas, que significa una o mas repeticiones; la interrogacion, que significa cero o una repeticion; la barra vertical, que es alternativa o OR; y los parentesis para agrupar. Las llaves con un numero indican repeticiones exactas.

## grep y egrep

Grep busca patrones en ficheros o en la entrada estandar. La sintaxis es grep patron fichero. Las opciones principales son: menos i para ignorar mayusculas, menos v para invertir la busqueda mostrando las lineas que no coinciden, menos c para contar coincidencias, y menos n para mostrar numeros de linea.

Egrep es grep con expresiones regulares extendidas. Es equivalente a grep menos E. Permite usar el mas, la interrogacion, la barra vertical y los parentesis sin necesidad de escaparlos.

Ejemplo de uso: para buscar todas las lineas que contienen exactamente tres digitos, usas egrep de comilla circunflejo corchete cero nueve corchete llaves tres dolar comilla fichero.

## sed: el editor de flujo

Sed procesa texto linea por linea aplicando transformaciones. El uso mas comun es la sustitucion: sed de comilla s barra viejo barra nuevo barra g comilla. La s indica sustitucion, las barras separan el patron de busqueda, el reemplazo, y la g al final significa global, es decir, que cambia todas las ocurrencias en cada linea, no solo la primera.

Otros usos de sed: borrar lineas que coincidan con un patron con sed de comilla barra patron barra d comilla. Borrar un rango de lineas por numero: sed dos coma cinco d borra las lineas de la dos a la cinco. Imprimir solo ciertas lineas con la opcion menos n y el comando p.

Sed es muy potente para transformar texto automaticamente. En tus scripts lo usaras frecuentemente para normalizar nombres de fichero, cambiar extensiones, eliminar espacios extra, y cosas similares.

## awk: procesamiento de campos

Awk es un lenguaje de programacion para procesar texto campo por campo. Por defecto, divide cada linea en campos separados por espacios. El primer campo es dolar uno, el segundo dolar dos, y asi sucesivamente. Dolar cero es la linea completa. La variable NF contiene el numero de campos, y NR el numero de linea.

La sintaxis basica es awk de comilla llaves print dolar uno llaves comilla fichero, que imprime el primer campo de cada linea. Puedes especificar un separador distinto con la opcion menos F. Por ejemplo, awk menos F dos puntos de comilla llaves print dolar tres llaves comilla es util para procesar el fichero passwd, donde los campos estan separados por dos puntos.

Awk tambien permite condicionales: awk de comilla dolar tres mayor que mil llaves print dolar uno llaves comilla imprime el primer campo de las lineas cuyo tercer campo sea mayor que mil.

## sort: ordenar

Sort ordena lineas de texto. Las opciones principales son: menos n para ordenar numericamente en vez de lexicograficamente, menos r para orden inverso, menos k para especificar la columna de ordenacion, y menos t para especificar el separador de campos. Por ejemplo, sort menos n menos k dos ordena por la segunda columna numericamente.

Menos u elimina duplicados al ordenar, y menos o permite escribir la salida al mismo fichero de entrada de forma segura.

## uniq: eliminar duplicados

Uniq elimina lineas duplicadas consecutivas. Es importante: las lineas deben estar ordenadas para que uniq funcione, por eso casi siempre se usa despues de sort. Las opciones principales son: menos c para contar cuantas veces aparece cada linea, y menos d para mostrar solo las duplicadas.

Un patron muy comun es: sort fichero barra vertical uniq menos c barra vertical sort menos rn, que ordena, cuenta duplicados y muestra los mas frecuentes primero.

## find: buscar ficheros

Find busca ficheros en el sistema de ficheros. La sintaxis es find directorio opciones. Los filtros principales son: menos name para buscar por nombre con comodines, menos type f para buscar solo ficheros regulares, menos type d para solo directorios. Se pueden combinar filtros con menos o para OR y con parentesis.

Ejemplo: find punto menos type f menos name asterisco punto c menos print busca todos los ficheros punto c recursivamente desde el directorio actual.

Menos print0 imprime los nombres terminados en null en vez de nueva linea, lo que es mas seguro para ficheros con espacios en el nombre. Se usa con xargs menos cero.

## du: espacio en disco

Du muestra el espacio que ocupa un directorio. Las opciones principales son: menos s para mostrar solo el total, menos h para formato legible con kilobytes y megabytes, y menos k para mostrar en kilobytes.

## head y tail: principio y final

Head muestra las primeras lineas de un fichero. Tail muestra las ultimas. La opcion menos n especifica cuantas lineas. Tail menos f sigue mostrando nuevas lineas a medida que se anaden al fichero, util para monitorizar logs.

## cut y paste: extraer y pegar columnas

Cut extrae campos o caracteres de cada linea. Las opciones son: menos f para especificar campos, menos d para el delimitador, y menos c para caracteres por posicion. Paste hace lo contrario: une lineas de varios ficheros lado a lado.

## tr: traducir caracteres

Tr reemplaza o elimina caracteres. La sintaxis es tr conjunto1 conjunto2, donde cada caracter del conjunto uno se reemplaza por el correspondiente del conjunto dos. La opcion menos d elimina caracteres. Ejemplos utiles: tr A-Z a-z convierte a minusculas, tr menos d cero-nueve elimina todos los digitos, y tr espacio guion bajo convierte espacios en guiones bajos.

## xargs: construir comandos

Xargs lee datos de la entrada estandar y los pasa como argumentos a un comando. Es util para combinar find con otros comandos. El patron mas comun es: find punto menos name asterisco punto o barra vertical xargs rm menos f, que busca y borra todos los ficheros punto o.

La opcion menos cero junto con find menos print0 maneja correctamente ficheros con espacios o caracteres especiales en el nombre.

## join: union relacional

Join hace un inner join entre dos ficheros ordenados por una columna clave. Los dos ficheros deben estar ordenados por la columna de union. La opcion menos uno N especifica la columna clave del primer fichero, y menos dos N la del segundo.

## Redirecciones y pipes

En el shell, mayor que redirige la salida estandar a un fichero truncandolo. Doble mayor que anade al final sin truncar. Dos mayor que redirige la salida de error. Dos mayor que ampersand uno redirige la salida de error a la salida estandar. Menor que toma la entrada desde un fichero.

La barra vertical conecta la salida de un comando con la entrada del siguiente. Se pueden encadenar multiples pipes: comando uno barra vertical comando dos barra vertical comando tres.

Estos son los bloques basicos para construir scripts potentes. La filosofia Unix es combinar herramientas simples con pipes para resolver problemas complejos.
