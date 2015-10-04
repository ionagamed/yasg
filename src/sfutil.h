#pragma once

#include "libs.h"

namespace sf {
double angleBetween (
		const sf::Vector2f& a,
		const sf::Vector2f& b);
double dotProduct (
		const sf::Vector2f& a,
		const sf::Vector2f& b);
double crossProduct (
		const sf::Vector2f& a,
		const sf::Vector2f& b);
sf::Vector2f rotate (
		const sf::Vector2f& vec,
		double angle);
double degToRad(double theta);
double radToDeg(double theta);
double magnitude(const sf::Vector2f& vec);
sf::Vector2f normalize(const sf::Vector2f& vec);

/// Does the linear interpolation
//
/// The same as (b - a) * x + a
double interpolate(double a, double b, double x);

/// Multiply every component of RGB color c by m
//
/// WARNING: sf::Color uses uint8_t to store the data
/// 		 so the multiplication is not lossless
sf::Color operator * (const sf::Color& c, double m);

sf::Color vectorToColor (
		const sf::Vector3f& vec, 
		uint8_t a = 255);
sf::Vector3f colorToVector (
		const sf::Color& color);
};
