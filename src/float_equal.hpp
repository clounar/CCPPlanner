#ifndef FLOAT_EQUAL_HPP
#define FLOAT_EQUAL_HPP

#define FLOAT_EPS_DEF(_name,_feps,_deps,_ldeps) template<typename T> struct _name;                                                                                              \
template<> struct _name<float> { static_assert(_feps >= 0, "The eps must be greater than 0"); static constexpr float eps = static_cast<float>(_feps); };                        \
template<> struct _name<double> { static_assert(_deps >= 0, "The eps must be greater than 0"); static constexpr double eps = static_cast<double>(_deps); };                     \
template<> struct _name<long double> { static_assert(_ldeps >= 0, "The eps must be greater than 0"); static constexpr long double eps = static_cast<long double>(_ldeps); };	

namespace feqv
{
	FLOAT_EPS_DEF(DefaultEps, 1e-6, 1e-10, 1e-33);
	
	template<template<typename> class EpsDef = DefaultEps, typename T>
		inline bool isEqual(T a, T b)
		{
			return (a > b ? a - b : b - a) < EpsDef<T>::eps;
		}

	template<typename T, typename eps_T>
		inline bool isEqual(T a, T b, eps_T eps)
		{
			return (a > b ? a - b : b - a) < static_cast<T>(eps);
		}

	template<template<typename> class EpsDef = DefaultEps, typename T>
		inline bool isEqualZero(T a)
		{
			return (a < static_cast<T>(0.0) ? a > -EpsDef<T>::eps : a < EpsDef<T>::eps);
		}

	template<typename T, typename eps_T>
		inline bool isEqualZero(T a, eps_T eps)
		{
			return (a < static_cast<T>(0.0) ? a > static_cast<T>(-eps) : a < static_cast<T>(eps));
		}
}
#endif /*!FLOAT_EQUAL_HPP*/
