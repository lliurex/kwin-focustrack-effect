uniform float borderWidth;
uniform float aspect;  // ratio of width to height
varying vec2 wdgCoord;
uniform sampler2D sampler;

void main() {
    vec4 g_Color = texture2D(sampler, wdgCoord);
    vec3 lms;
    vec3 outputColor = g_Color.rgb;
    float maxX = 1.0 - borderWidth;
    float minX = borderWidth;
    float maxY = maxX / aspect;
    float minY = minX / aspect;
    gl_FragColor = g_Color;
}
