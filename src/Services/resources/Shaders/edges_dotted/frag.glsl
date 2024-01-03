// #version 410 core


// uniform vec4 PointColor;
// out vec4 FragColor;

// void main() {
// FragColor = PointColor;
// }



#version 330

flat in vec3 startPos;
in vec3 vertPos;

out vec4 fragColor;

uniform vec2  Resolution;
uniform float DashSize;
uniform float GapSize;
uniform vec4 PointColor;

void main()
{
    vec2  dir  = (vertPos.xy-startPos.xy) * Resolution/2.0;
    float dist = length(dir);

    if (fract(dist / (DashSize + GapSize)) > DashSize/(DashSize + GapSize))
        discard;
    fragColor = PointColor;
}



// #version 410 core

// flat in vec3 startPos;
// in vec3 vertPos;

// out vec4 fragColor;

// uniform vec2  Resolution;
// uniform uint  Pattern;
// uniform float Factor;

// uniform vec4 PointColor;

// void main()
// {
//     vec2  dir  = (vertPos.xy-startPos.xy) * Resolution/2.0;
//     float dist = length(dir);

//     uint bit = uint(round(dist / Factor)) & 15U;
//     if ((Pattern & (1U<<bit)) == 0U)
//         discard;
//     fragColor = PointColor;
// }


// #version 410 core

// // Входные данные от вершинного шейдера
// in vec2 fragCoord;

// // Выходной цвет фрагмента
// out vec4 fragColor;

// // Размер пунктирной линии
// const float dashSize = 0.03;
// const float gapSize = 0.02;

// void main()
// {
//     // Определяем координату x текущего фрагмента
//     float x = mod(fragCoord.x, 1.0);

//     // Определяем, находится ли фрагмент внутри сегмента пунктирной линии
//     float segment = mod(x, dashSize + gapSize);

//     // Если фрагмент находится внутри сегмента пунктирной линии, то окрашиваем его в белый цвет, иначе - в черный
//     if (segment &lt; dashSize)
//         fragColor = vec4(1.0, 1.0, 1.0, 1.0);
//     else
//         fragColor = vec4(0.0, 0.0, 0.0, 1.0);
// }
