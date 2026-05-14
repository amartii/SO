# Tema 9: Sistemas de Ficheros y Gestion de Discos

Este tema cubre como se organizan los datos en disco y como el sistema operativo gestiona el almacenamiento persistente.

## Estructura de un disco

Un disco duro se divide en particiones. Hay dos esquemas de particionado principales. El esquema MBR, que es el clasico, tiene un sector de arranque al principio del disco que contiene el codigo de inicio y una tabla de particiones con hasta cuatro particiones primarias. Si necesitas mas, una de las primarias se convierte en extendida, que puede contener multiples particiones logicas.

El esquema GPT es el moderno. Usa una cabecera al principio y otra al final del disco como copia de seguridad. Permite hasta ciento veintiocho particiones sin necesidad de particiones extendidas. Usa identificadores unicos globales llamados GUID para identificar cada particion.

## Asignacion de espacio en disco

Hay tres metodos principales para asignar espacio a ficheros en disco. El primero es la asignacion contigua, donde cada fichero ocupa un bloque contiguo de disco. Es simple y rapida para lectura secuencial, pero sufre de fragmentacion externa.

El segundo es la asignacion con lista enlazada, donde cada bloque del fichero contiene un puntero al siguiente bloque. No hay fragmentacion externa, pero el acceso aleatorio es lento porque hay que recorrer la lista.

El tercer metodo es la asignacion con lista enlazada con tabla, que es el metodo FAT. Los punteros se sacan de los bloques de datos y se ponen en una tabla en memoria. Asi, los bloques son completamente para datos y la tabla permite recorrer la cadena sin acceder a disco. El problema es que la tabla puede ser grande.

## El sistema FAT

En FAT, la tabla de asignacion de ficheros mapea cada cluster al siguiente cluster de la cadena. Las entradas de directorio contienen el nombre del fichero, sus atributos y el numero del primer cluster. Para leer un fichero, empiezas por su primer cluster y sigues la cadena en la tabla FAT hasta encontrar el marcador de fin.

Pregunta de examen: en FAT, los nombres de ficheros y directorios estan en las entradas de directorio. La tabla FAT solo contiene punteros a los siguientes clusters.

## Los i-nodos y el sistema Unix

Los sistemas de ficheros estilo Unix usan i-nodos. Un i-nodo es una estructura que contiene todos los metadatos de un fichero: permisos, propietario, tamaño, tiempos de acceso y modificacion, y las referencias a los bloques de datos.

El i-nodo usa un esquema combinado de asignacion indexada. Tiene punteros directos que apuntan directamente a bloques de datos, para ficheros pequenos. Tiene un puntero indirecto simple que apunta a un bloque que contiene punteros a bloques de datos. Tiene un puntero indirecto doble que apunta a un bloque de punteros a bloques de punteros a bloques de datos. Y puede tener un puntero indirecto triple para ficheros aun mas grandes.

Un directorio en Unix no es mas que un fichero que contiene una tabla de pares nombre e i-nodo. Cada entrada del directorio asocia un nombre con un numero de i-nodo.

Pregunta de examen: en un sistema con i-nodos se usa asignacion indexada con esquema combinado, que mezcla punteros directos e indirectos.

## Enlaces duros y simbolicos

Un enlace duro es un nombre adicional para un fichero existente. Cuando haces ln a b, la entrada de directorio de b apunta al mismo i-nodo que a. El campo st nlink del i-nodo se incrementa a dos. Ambos nombres son equivalentes: no hay original ni copia.

Cuando borras un nombre con unlink o rm, st nlink se decrementa. El fichero solo se borra realmente cuando st nlink llega a cero y ningun proceso tiene el fichero abierto. Esto es pregunta clasica de examen: si creas un enlace duro de a a b y luego borras a, el fichero sigue existiendo a traves de b con st nlink igual a uno.

Un enlace simbolico es un fichero especial que contiene la ruta de otro fichero. Si el fichero destino se borra, el enlace simbolico queda roto. Son mas flexibles que los duros porque pueden apuntar a ficheros en otros sistemas de ficheros y a directorios.

## Flock: bloqueo de ficheros

La funcion flock implementa un mecanismo de bloqueo de ficheros para coordinar el acceso entre multiples procesos. Soporta bloqueos compartidos para lectura, donde multiples procesos pueden tener el fichero bloqueado para lectura simultaneamente, y bloqueos exclusivos para escritura, donde solo un proceso puede tener el bloqueo. Es un lock de lectores y escritores aplicado a ficheros.

Pregunta de examen: flock sirve para un lock de lectores y escritores en ficheros. No confundirlo con flock como cerrojo de procesos.

## VFS: el sistema de ficheros virtual

El VFS es una capa de abstraccion en el kernel que permite que el sistema operativo use diferentes tipos de sistemas de ficheros de forma transparente. Todos los sistemas de ficheros implementan la misma interfaz, y el VFS se encarga de dirigir cada operacion al sistema de ficheros correcto. Asi, un proceso puede acceder a ext4, NTFS, NFS y otros de la misma manera.

## FUSE: sistemas de ficheros en espacio de usuario

FUSE permite implementar sistemas de ficheros fuera del kernel, en espacio de usuario. En vez de escribir un modulo del kernel, escribes un programa normal que responde a las operaciones de ficheros. El kernel redirige las llamadas al programa FUSE a traves de un dispositivo especial. Esto es mas lento pero mucho mas seguro y facil de desarrollar.

## LVM: gestion de volumenes logicos

LVM es una capa de abstraccion sobre las particiones fisicas. Agrupa discos fisicos en un pool llamado grupo de volumenes, del que se pueden crear volumenes logicos de cualquier tamaño. Permite redimensionar particiones en caliente y extender volumenes sobre multiples discos.

## RAID

RAID combina multiples discos para mejorar rendimiento, fiabilidad, o ambos. RAID cero divide los datos entre discos, mejorando velocidad pero sin redundancia. RAID uno duplica los datos en dos discos, ofreciendo redundancia. RAID cinco distribuye datos y paridad entre tres o mas discos, ofreciendo un equilibrio entre rendimiento y redundancia.

## Algoritmos de planificacion de disco

Para discos magneticos con cabezales moviles, el orden en que se atienden las solicitudes afecta al rendimiento. El algoritmo FCFS atiende en orden de llegada. El algoritmo SSTF atiende la solicitud mas cercana a la posicion actual del cabezal. El algoritmo SCAN mueve el cabezal de un extremo a otro atendiendo solicitudes, como un ascensor. El algoritmo C-SCAN es similar pero solo atiende en una direccion y al llegar al final vuelve al principio sin atender.

Estos algoritmos son cada vez menos relevantes con los discos de estado solido, que no tienen cabezal movil, pero siguen siendo materia de examen.
