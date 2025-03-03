# FdF -Fil de Fer
***This project involves representing a wireframe landscape in 3D.***\
:memo: ***Version: 3.1***:bulb:\
<img src='https://miro.medium.com/v2/resize:fit:1100/format:webp/1*vYsR345fPZhMouQP5vSIBg.png' width="300" height="150">\
| ***Program name***      | ***fdf***|
| ----------- | ----------- |
| **Turn in files**      | **Makefile,\*.h,\*.c, demo .fdf files*** |
| **External functs**   | **open, close, read, write,malloc, free, perror, strerror, exit • All functions of the math library (-lm compiler option, man 3 math on some operating systems) • All functions of the MiniLibX • ft_printf and any equivalent YOU coded** | **Description**   | **This project involves creating a simple wireframe model of a landscape.**|

:exclamation::exclamation: **Map parsing:**\
    ***What is a valid map!!?***\
        `For this very project , Any kind of map is valid, And it is up to the programmed to decide how to\
        handle the map. As long as it doesn't cause some segfaults or program crash.`\
        :scroll: **Project subject.pdf**:\
        ``` Keep in mind that the goal of this project is not to parse maps! However, this doesn’t\
        mean that your program should crash when run. It means that we assume the map\
        contained in the file is properly formatted.```
    
## Isometric projection
    Isometric projection
    Isometric (meaning “equal measure”) is a type of parallel (axonometric) projection,
    where the X and Z axes are inclined to the horizontal plane at the angle of 30⁰.
    The angle between axonometric axes equals 120⁰.

**It means that to represent a 3D object in a 2D demension which is our window | img ,  We're going to iso-project each of the points cordinates given by the map to a surface 2D cordinates: (x, y, z) --> (x, y)**\
\
***"A perfect cube in an isometric projection would look like a perfect hexagon."***

\
<img height='230' width='400' src='https://miro.medium.com/v2/resize:fit:1100/format:webp/1*ywa_sqeyyAIf7bqY6wieIg.png'>
<img height='230' width='400' src='https://miro.medium.com/v2/resize:fit:1400/format:webp/1*590KMJC064Z1ioKFSPMEIQ.jpeg'>
___
:bulb: *More info of isometric-projection:*\
\
**[Isometric projection principals](https://medium.com/gravitdesigner/designers-guide-to-isometric-projection-6bfd66934fc7)**\
**[Isometric projection for games-developement](https://pikuma.com/blog/isometric-projection-in-games)**
____
