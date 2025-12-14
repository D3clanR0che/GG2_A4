attribute vec2 a_position;
attribute vec4 a_color;
attribute vec2 a_uv;

uniform float u_time;
uniform vec2 u_objectScale;
uniform float u_objectAngle;
uniform vec2 u_objectPosition;
uniform vec2 u_cameraPosition;
uniform vec2 u_projectionScale;
uniform vec2 u_uvScale;
uniform vec2 u_uvOffset;

varying vec4 v_color;
varying vec2 v_uv;

vec2 getWorldPosition(vec2 objectSpacePosition);

void main()
{
	vec2 objectSpacePosition = a_position;
	vec2 worldSpacePosition = getWorldPosition( objectSpacePosition );
	vec2 viewSpacePosition = worldSpacePosition - u_cameraPosition;
	vec2 clipSpacePosition = viewSpacePosition * u_projectionScale;

	gl_Position = vec4( clipSpacePosition, 0.0, 1.0 );

	v_color = a_color;
	v_uv = a_uv * u_uvScale + u_uvOffset;
}

vec2 getWorldPosition(vec2 objectSpacePosition)
{
	// Scale.
	vec2 worldPosition = objectSpacePosition * u_objectScale;

	// Rotate.
	worldPosition = vec2(
		worldPosition.x * cos(u_objectAngle) - worldPosition.y * sin(u_objectAngle),
		worldPosition.x * sin(u_objectAngle) + worldPosition.y * cos(u_objectAngle)
	);

	// Translate.
	worldPosition += u_objectPosition;

	return worldPosition;
}
