#pragma once
#include <string>

#define SIGN_UP_REQUEST_CODE 10
#define LOGIN_REQUEST_CODE 20
#define ERROR_RESPONSE_CODE 50


struct LoginRequest {
	std::string username;
	std::string password;
};

struct SignupRequest : public LoginRequest {
	std::string email;
};