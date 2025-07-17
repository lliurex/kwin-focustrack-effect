uniform float borderWidth;
varying float aspect;  // ratio of width to height
varying vec2 wdgCoord;
uniform sampler2D sampler;

vec3 colorize(vec3 rgb) {
    return vec3(
        (100.0) + (0.0) + (0.0),
        (100.0) + (0.0) + (0.0),
        (100.0) + (0.0) + (0.0)
    );
}
void main() {
    vec4 g_Color = texture2D(sampler, wdgCoord);
    vec3 lms;
    vec3 outputColor = colorize(g_Color.rgb);
	aspect=1.1;
    float maxX = 1.0 - borderWidth;
    float minX = borderWidth;
    float maxY = maxX / aspect;
    float minY = minX / aspect;
    g_Color.rgb = outputColor;
    gl_FragColor = g_Color;
}
