#include "sfutil.h"

#include <cmath>
#define PI 3.14159265358

namespace sf {
double angleBetween (
		const sf::Vector2f& a,
		const sf::Vector2f& b) {
	return std::atan2(
			crossProduct(a, b),
			dotProduct(a, b));
}

double dotProduct (
		const sf::Vector2f& a,
		const sf::Vector2f& b) {
	return a.x * b.x + a.y * b.y;
}

double crossProduct (
		const sf::Vector2f& a,
		const sf::Vector2f& b) {
	return a.x * b.y - a.y * b.x;
}

sf::Vector2f rotate (
		const sf::Vector2f& vec, 
		double angle) {
	sf::Vector2f ret;
	ret.x = vec.x * cos(angle) - vec.y * sin(angle);
	ret.y = vec.x * sin(angle) + vec.y * cos(angle);
	return ret;
}

double degToRad(double theta) {
	return theta * PI / 180.0;
}
double radToDeg(double theta) {
	return theta * 180.0 / PI;
}

double magnitude(const sf::Vector2f& vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}
sf::Vector2f normalize(const sf::Vector2f& vec) {
	if (vec.x == 0 && vec.y == 0) {
		return vec;
	}
	return vec / (float) magnitude(vec);
}

double interpolate(double a, double b, double x) {
	return (b - a) * x + a;
}

sf::Color operator * (const sf::Color& c, double m) {
	double comp[3] = {
		(double) c.r, 
		(double) c.g, 
		(double) c.b
	};
	for (int i = 0; i < 3; i++) {
		comp[i] *= m;
	}
	return sf::Color(
			comp[0],
			comp[1],
			comp[2]
			);
}

sf::Color vectorToColor (
		const sf::Vector3f& vec,
		uint8_t a) {
	return sf::Color(
			(uint8_t) vec.x,
			(uint8_t) vec.y,
			(uint8_t) vec.z,
			a
			);
}
sf::Vector3f colorToVector (
		const sf::Color& color) {
	return sf::Vector3f(
			(double) color.r,
			(double) color.g,
			(double) color.b
			);
}
};
