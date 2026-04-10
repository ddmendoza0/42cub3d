ORDEN ARCHIVO .cub
## assets/maps/error_test/archivo_cub/error_test_order_1.cub 
   1. F/C
    2. TEXTURAS
     3. MAPA

@ No muestra mensaje de error


## assets/maps/error_test/archivo_cub/error_test_order_2.cub
   1. F/C
    2. MAPA
     3. TEXTURAS

> Error
> Missing identifier: NO

## assets/maps/error_test/archivo_cub/error_test_order_3.cub
   1. MAPA
    2. TEXTURA
     3. F/C

> Error
> Missing identifier: NO

--------------------------------------------------------------------------------

COLOR --> TODO OK
/*## assets/maps/error_test/color/error_color_dup.cub
   F 120,85,50
   C 100,160,220
   C 100,260,200

> Error
> Duplicate identifier: C
@ Salta el mensaje de error pero se ejecuta igual


## assets/maps/error_test/color/error_color_intmax1.cub
   F 1200000000000000000000000000000000,85,50
   C 100,160,220

@ Se ejecuta igualmente 


## assets/maps/error_test/color/error_color_intmax2.cub
   F 120,85,50
   C 100,16666666666666666666666666660,220

> Error
> RGB values must be in range [0-255]
@ Se ejecuta igualmente


## assets/maps/error_test/color/error_color_negativo.cub
   F 120,85,50
   C 100,160,-220

> Error
> RGB values must be in range [0-255]
@ Se ejecuta igualmente


## assets/maps/error_test/color/error_no_color.cub
   F 120,85,50
   C 

@ Se ejecuta igualmente sin mensaje de error*/

--------------------------------------------------------------------------------

TEXTURAS --> TODO OK
/*## assets/maps/error_test/textura/text_dup.cub
   NO ./assets/textures/north.png
   SO ./assets/textures/south.png
   SO ./assets/textures/south.png
   WE ./assets/textures/west.png
   EA ./assets/textures/east.png
   DO ./assets/textures/door.png

> Error
> Duplicate identifier: SO
> Error
> Missing identifier: WE
@ El segundo mensaje de error no deberia aparecer


## assets/maps/error_test/textura/text_no_existe.cub
   NO ./assets/textures/north.png
   SO ./assets/textures/south.png
   WE ./assets/textures/west.png
   EA ./assets/textures/waldo.png
   DO ./assets/textures/door.png

> Error
> Cannot open texture file: ./assets/textures/waldo.png
> Error
> Missing identifier: F
@ El segundo mensaje de error no deberia aparecer


## assets/maps/error_test/textura/text_ruta_sin_archivo.cub
   NO ./assets/textures/north.png
   SO ./assets/textures/south.png
   WE ./assets/textures/
   EA ./assets/textures/east.png
   DO ./assets/textures/door.png

   F 120,85,50
   C 100,160,220

> Error
> Texture file must have .png extension: ./assets/textures/
> Error
> Missing identifier: EA
@ El segundo mensaje de error no deberia aparecer


## assets/maps/error_test/textura/text_sin_formato.cub
   NO ./assets/textures/north.png
   SO ./assets/textures/south.png
   WE ./assets/textures/west.png
   EA ./assets/textures/east
   DO ./assets/textures/door.png

> Error
> Texture file must have .png extension: ./assets/textures/east
> Error
> Missing identifier: F
@ El segundo mensaje de error no deberia aparecer*/

--------------------------------------------------------------------------------

MAPA
/*## assets/maps/error_test/mapa/error_isla_puerta.cub
   111111111111111111111
   100000000000000000001
   101111111111111111101
   101               101
   101 DDDDDDDDDDDDD 101
   101 D00000N00000D 101
   101 DDDDDDDDDDDDD 101
   101               101
   101111111111111111101
   100000000000000000001
   111111111111111111111
@ Lo ejecuta normal a pesar de que es una isla de puertas*/


## assets/maps/error_test/mapa/error_mapa_isla_extern_open.cub
   111111111111111111111
   100000000000000000001
   101111111111111111101
   101               101
   101 1111111111111 101   111
   101 100000N000001 101   10
   101 1111111111111 101   111
   101               101
   101111111111111111101
@ Se ejecuta a pesar de estar abierto


/*## assets/maps/error_test/mapa/error_mapa_isla_puerta_mal.cub 
   111111111111111111111
   100000000000000000001
   101111111111111111101
   101               101
   101 111111D111111 101
   101 100000N000001 101
   101 1111111111111 101
   101               101
   101111111111111111101
   100000000000000000001
   111111111111111111111
@ Se ejecuta a pesar de tener una puerta mirando al vacio*/


## assets/maps/error_test/mapa/error_mapa_puerta_fuera.cub
   100000000000000000001
   101111111111111111101
   101               101
   101 1111111111111 101
   101 100000N000001 101     D
   101 1111111111111 101
   101               101
   101111111111111111101
   100000000000000000001
   111111111111111111111
@ Se ejecuta a pesar de haber una puerta sola
