/*
 * margs - Maipa's Args Analyzer
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/margs/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#include "margs_types.hpp"
#include "arg_value.hpp"

namespace WORKAROUND {

	#include <stdint.h>

	void GetUnsigned (
		uint16_t& value,
		const uint16_t& stringCount,
		const char* const& string
	) {
		uint16_t isNotValidNumber = 0;
		uint16_t i = 0;
		
		value = 0;
		for (; i < stringCount; ++i) {
			isNotValidNumber += (string[i] - '0') > 10;
			value = value * 10 + (string[i] - '0');
		}

		// TODO
		// Implement what happends if ERROR.
		//if (isNotValidNumber) ERROR ();
	}

	void GetSigned (
		int16_t& value,
		const int16_t& stringCount,
		const char* const& string
	) {
		int16_t isNotValidNumber = 0;
		int16_t i = 0;

		if (string[0] == '-') ++i;
		
		value = 0;
		for (; i < stringCount; ++i) {
			isNotValidNumber += (string[i] - '0') > 10;
			value = value * 10 + (string[i] - '0');
		}

		if (string[0] == '-') value *= -1;

		// TODO
		// Implement what happends if ERROR.
		//if (isNotValidNumber) ERROR ();
	}

}

namespace margs {
	// arithmetic and default
	template<class T>
	struct decoder {
		static bool decode(const arg_value& lhs, T& rhs) {
			// arithmetic
			if constexpr (std::is_arithmetic_v<T>) {
				if (!lhs.isScalar()) return false;

				const std::string& scalar = lhs.as<std::string>();

				// integral
				if constexpr (std::is_integral_v<T>) {
					// signed
					if constexpr (std::is_signed_v<T>) {
						// TODO needs testing !
						//rhs = WORKAROUND::GetSigned (rhs, scalar.length(), scalar.c_str());
						return false;
						//return ston(scalar, rhs);
					}
					// unsigned
					else {
						const auto& characters = scalar.c_str(); 
						WORKAROUND::GetUnsigned (rhs, scalar.length(), characters);
						return true;
						//return stoun(scalar, rhs);
					}
				}
				// floating-point
				else {
					return stofp(scalar, rhs);
				}
			}
			// default
			else {
				return false;
			}
		}
	};

	// true, 1 | false, 0
	template<>
	struct decoder<bool> {
		static bool decode(const arg_value& lhs, bool& rhs) {
			if (!lhs.isScalar()) return false;

			const std::string& arg_value = lhs.as<std::string>();

			if (arg_value == "true" || arg_value == "1") {
				rhs = true;
			}
			else if (arg_value == "false" || arg_value == "0") {
				rhs = false;
			}
			else {
				return false;
			}

			return true;
		}
	};

	template<class T>
	struct decoder<std::vector<T>> {
		static bool decode(const arg_value& lhs, std::vector<T>& rhs) {
			if (!lhs.isSequence()) return false;

			rhs.clear();
			rhs.reserve(lhs.size());
			for (const arg_value& elem : lhs) {
				rhs.push_back(elem.as<T>());
			}

			return true;
		}
	};
}