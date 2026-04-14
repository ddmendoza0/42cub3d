ORDEN ARCHIVO .cub - OK
/*## assets/maps/error_test/archivo_cub/error_test_order_1.cub
   1. F/C
    2. TEXTURAS
     3. MAPA

@ OUTPUT OK - RUN

## assets/maps/error_test/archivo_cub/error_test_order_2.cub
   1. F/C
    2. MAPA
     3. TEXTURAS

> Error
> Missing identifier: NO
@ OUTPUT OK - NO RUN

## assets/maps/error_test/archivo_cub/error_test_order_3.cub
   1. MAPA
    2. TEXTURA
     3. F/C

> Error
> Missing identifier: NO
@ OUTPUT OK - NO RUN


## assets/maps/error_test/archivo_cub/valid_compressed_ids.cub
    Todos los ids sin separaciones de salto de linia.

@ OUTPUT OK - RUN

*/

--------------------------------------------------------------------------------

COLOR --> TODO OK
/*## assets/maps/error_test/color/error_color_dup.cub
   F 120,85,50
   C 100,160,220
   C 100,260,200

> Error
> Duplicate identifier: C
@ OUTPUT OK - NO RUN


## assets/maps/error_test/color/error_color_intmax1.cub
   F 1200000000000000000000000000000000,85,50
   C 100,160,220

> Error
> RGB values must be in range [0-255]
@ OUTPUT OK - NO RUN


## assets/maps/error_test/color/error_color_intmax2.cub
   F 120,85,50
   C 100,16666666666666666666666666660,220

> Error
> RGB values must be in range [0-255]
@ OUTPUT OK - NO RUN


## assets/maps/error_test/color/error_color_negativo.cub
   F 120,85,50
   C 100,160,-220

> Error
> RGB values must be in range [0-255]
@ OUTPUT OK - NO RUN


## assets/maps/error_test/color/error_no_color.cub
   F 120,85,50
   C 

> Error
> RGB must have exactly 3 values
@ OUTPUT OK - NO RUN
*/

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
@ OUTPUT OK - NO RUN


## assets/maps/error_test/textura/text_no_existe.cub
   NO ./assets/textures/north.png
   SO ./assets/textures/south.png
   WE ./assets/textures/west.png
   EA ./assets/textures/waldo.png
   DO ./assets/textures/door.png

> Error
> Cannot open texture file: ./assets/textures/waldo.png
@ OUTPUT OK - NO RUN


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
@ OUTPUT OK - NO RUN


## assets/maps/error_test/textura/text_sin_formato.cub
   NO ./assets/textures/north.png
   SO ./assets/textures/south.png
   WE ./assets/textures/west.png
   EA ./assets/textures/east
   DO ./assets/textures/door.png

> Error
> Texture file must have .png extension: ./assets/textures/east
@ OUTPUT OK - NO RUN
*/

--------------------------------------------------------------------------------

MAPA -- OK
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

> Error
> Map is not closed by walls
@ OUTPUT OK - NO RUN


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

> Error
> Map is not closed by walls
@ OUTPUT OK - NO RUN


## assets/maps/error_test/mapa/error_mapa_isla_puerta_mal.cub 
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

> Error
> Map is not closed by walls
@ OUTPUT OK - NO RUN


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

> Error
> Map is not closed by walls
@ OUTPUT OK - NO RUN


## assets/maps/error_test/mapa/error_first_line_map1.cub
    N11111
    100001
    100001
    111111

> Error
> Map is not closed by walls
@ OUTPUT OK - NO RUN


## assets/maps/error_test/mapa/error_first_line_map2.cub
    D11111
    100001
    10N001
    111111

> Error
> Map is not closed by walls
@ OUTPUT OK - NO RUN

*/
