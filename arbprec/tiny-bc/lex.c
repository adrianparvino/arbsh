#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"

static const char* const keywords[] = {

    "auto",
    "break",
    "define",
    "for",
    "ibase",
    "if",
    "length",
    "obase",
    "quit",
    "return",
    "scale",
    "sqrt",
    "while",

};

static const uint32_t keyword_lens[] = {

    4,
    5,
    6,
    3,
    5,
    2,
    6,
    5,
    4,
    6,
    5,
    4,
    5,

};

static BcLexStatus bc_lex_whitespace(BcLex* lex, BcLexToken* token);
static BcLexStatus bc_lex_string(BcLex* lex, BcLexToken* token);
static BcLexStatus bc_lex_number(BcLex* lex, BcLexToken* token, char start);
static BcLexStatus bc_lex_key(BcLex* lex, BcLexToken* token);

BcLexStatus bc_lex_init(BcLex* lex, const char* text) {

	// Check for error.
	if (lex == NULL) {
		return BC_LEX_STATUS_INVALID_PARAM;
	}

	// Set the data.
	lex->buffer = text;
	lex->idx = 0;

	return BC_LEX_STATUS_SUCCESS;
}

BcLexStatus bc_lex_next(BcLex* lex, BcLexToken* token) {

	// Check for error.
	if (lex == NULL || token == NULL) {
		return BC_LEX_STATUS_INVALID_PARAM;
	}

	BcLexStatus status = BC_LEX_STATUS_SUCCESS;

	// Get the character.
	char c = lex->buffer[lex->idx];

	// Increment the index.
	++lex->idx;

	char c2;

	// This is the workhorse of the lexer.
	switch (c) {

		case '\0':
		{
			token->type = BC_LEX_EOF;
			break;
		}

		case '\t':
		{
			status = bc_lex_whitespace(lex, token);
			break;
		}

		case '\n':
		{
			token->type = BC_LEX_NEWLINE;
			break;
		}

		case '\v':
		case '\f':
		case '\r':
		case ' ':
		{
			status = bc_lex_whitespace(lex, token);
			break;
		}

		case '!':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// The only valid way to have a bang is a NOT_EQ token.
			// If it's not valid, we do not want to increment twice.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_REL_NOT_EQ;
			}
			else {
				token->type = BC_LEX_INVALID;
				status = BC_LEX_STATUS_INVALID_TOKEN;
			}

			break;
		}

		case '"':
		{
			status = bc_lex_string(lex, token);
			break;
		}

		case '%':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or as an assignment.
			// If it's an assignment, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_ASSIGN_MODULUS;
			}
			else {
				token->type = BC_LEX_OP_MODULUS;
			}

			break;
		}

		case '(':
		{
			token->type = BC_LEX_LEFT_PAREN;
			++lex->idx;
			break;
		}

		case ')':
		{
			token->type = BC_LEX_RIGHT_PAREN;
			++lex->idx;
			break;
		}

		case '*':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or as an assignment.
			// If it's an assignment, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_ASSIGN_MULTIPLY;
			}
			else {
				token->type = BC_LEX_OP_MULTIPLY;
			}

			break;
		}

		case '+':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or as an assignment.
			// If it's an assignment, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_ASSIGN_PLUS;
			}
			else {
				token->type = BC_LEX_OP_PLUS;
			}

			break;
		}

		case ',':
		{
			token->type = BC_LEX_COMMA;
			break;
		}

		case '-':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or as an assignment.
			// If it's an assignment, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_ASSIGN_MINUS;
			}
			else if (isdigit(c2) || c2 == '.') {
				status = bc_lex_number(lex, token, c);
			}
			else {
				token->type = BC_LEX_OP_MINUS;
			}

			break;
		}

		case '.':
		{
			status = bc_lex_number(lex, token, c);
			break;
		}

		case '/':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or as an assignment.
			// If it's an assignment, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_ASSIGN_DIVIDE;
			}
			else {
				token->type = BC_LEX_OP_DIVIDE;
			}

			break;
		}

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			status = bc_lex_number(lex, token, c);
			break;
		}

		case ';':
		{
			token->type = BC_LEX_SEMICOLON;
			break;
		}

		case '<':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or with an equals.
			// If with an equals, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_REL_LESS_EQ;
			}
			else {
				token->type = BC_LEX_OP_REL_LESS;
			}

			break;
		}

		case '=':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or with another equals.
			// If with another equals, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_REL_EQUAL;
			}
			else {
				token->type = BC_LEX_OP_ASSIGN;
			}

			break;
		}

		case '>':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or with an equals.
			// If with an equals, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_REL_GREATER_EQ;
			}
			else {
				token->type = BC_LEX_OP_REL_GREATER;
			}

			break;
		}

		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		{
			status = bc_lex_number(lex, token, c);
			break;
		}

		case '[':
		{
			token->type = BC_LEX_LEFT_BRACKET;
			break;
		}

		case '\\':
		{
			status = bc_lex_whitespace(lex, token);
			break;
		}

		case ']':
		{
			token->type = BC_LEX_RIGHT_BRACKET;
			break;
		}

		case '^':
		{
			// Get the next character.
			c2 = lex->buffer[lex->idx];

			// This character can either be alone or as an assignment.
			// If it's an assignment, we need to increment the index.
			if (c2 == '=') {
				++lex->idx;
				token->type = BC_LEX_OP_ASSIGN_POWER;
			}
			else {
				token->type = BC_LEX_OP_POWER;
			}

			break;
		}

		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		{
			status = bc_lex_key(lex, token);
			break;
		}

		case '{':
		{
			token->type = BC_LEX_LEFT_BRACE;
			break;
		}

		case '}':
		{
			token->type = BC_LEX_RIGHT_BRACE;
			break;
		}

		default:
		{
			// All other characters are invalid.
			token->type = BC_LEX_INVALID;
			status = BC_LEX_STATUS_INVALID_TOKEN;
			break;
		}
	}

	return status;
}

static BcLexStatus bc_lex_whitespace(BcLex* lex, BcLexToken* token) {

	// Set the token type.
	token->type = BC_LEX_WHITESPACE;

	// Get the character.
	char c = lex->buffer[lex->idx];

	// Eat all whitespace (and non-newline) characters.
	while ((isspace(c) && c != '\n') || c == '\\') {
		++lex->idx;
		c = lex->buffer[lex->idx];
	}

	return BC_LEX_STATUS_SUCCESS;
}

static BcLexStatus bc_lex_string(BcLex* lex, BcLexToken* token) {

	// Set the token type.
	token->type = BC_LEX_STRING;

	// Get the starting index and character.
	size_t i = lex->idx;
	char c = lex->buffer[i];

	// Find the end of the string, one way or the other.
	while (c != '"' && c != '\0') {
		c = lex->buffer[++i];
	}

	// If we have reached the end of the buffer, complain.
	if (c == '\0') {
		lex->idx = i;
		return BC_LEX_STATUS_NO_STRING_END;
	}

	// Calculate the length of the string.
	size_t len = i - lex->idx;

	// Figure out the number of backslash newlines in a string.
	size_t backslashes = 0;
	for (size_t j = lex->idx; j < i; ++j) {
		c = lex->buffer[j];
		backslashes += c == '\\' && lex->buffer[j + 1] == '\n' ? 1 : 0;
	}

	// Allocate the string.
	token->data.string = malloc(len - backslashes + 1);

	// Check for error.
	if (token->data.string == NULL) {
		return BC_LEX_STATUS_MALLOC_FAIL;
	}

	// The copy start and the number of backslash
	// hits. These are for the upcoming loop.
	const char* start = lex->buffer + lex->idx;
	size_t hits = 0;

	// Copy the string.
	for (size_t j = 0; j < len; ++j) {

		// Get the character.
		char c = start[j];

		// If we have hit a backslash, skip it.
		if (hits < backslashes && c == '\\' && start[j + 1] == '\n') {
			++hits;
			continue;
		}

		// Copy the character.
		token->data.string[j - hits] = c;
	}

	// Make sure to set the null character.
	token->data.string[len] = '\0';

	// Set the index. We need to go one
	// past because of the closing quote.
	lex->idx = i + 1;

	return BC_LEX_STATUS_SUCCESS;
}

static BcLexStatus bc_lex_number(BcLex* lex, BcLexToken* token, char start) {

	// Set the token type.
	token->type = BC_LEX_NUMBER;

	// Whether or not we already have passed a decimal point.
	int point = start == '.';

	// Get a pointer to the place in the buffer.
	const char* buffer = lex->buffer + lex->idx;

	// Cache these for the upcoming loop.
	size_t backslashes = 0;
	size_t i = 0;
	char c = buffer[i];

	// Find the end of the number.
	while (c && (isdigit(c) || (c >= 'A' && c <= 'F') || (c == '.' && !point) ||
	             (c == '\\' && buffer[i + 1] == '\n')))
	{
		// If we ran into a backslash, handle it.
		if (c == '\\') {
			++i;
			backslashes += 1;
		}

		// Increment and get the character.
		c = buffer[++i];
	}

	// Calculate the length of the string.
	size_t len = i - lex->idx + 1;

	// Allocate the string.
	token->data.string = malloc(len - backslashes + 1);

	// Check for error.
	if (token->data.string == NULL) {
		return BC_LEX_STATUS_MALLOC_FAIL;
	}

	// Set the starting character.
	token->data.string[0] = start;

	// The copy start and the number of backslash
	// hits. These are for the upcoming loop.
	const char* buf = buffer - 1;
	size_t hits = 0;

	// Copy the string.
	for (size_t j = 1; j < len; ++j) {

		// Get the character.
		char c = buf[j];

		// If we have hit a backslash, skip it.
		// We don't have to check for a newline
		// because it's guaranteed.
		if (hits < backslashes && c == '\\') {
			++hits;
			++j;
			continue;
		}

		// Copy the character.
		token->data.string[j - (hits * 2)] = c;
	}

	// Make sure to set the null character.
	token->data.string[len] = '\0';

	// Set the index. We need to go one
	// past because of the closing quote.
	lex->idx += i;

	return BC_LEX_STATUS_SUCCESS;
}

static BcLexStatus bc_lex_key(BcLex* lex, BcLexToken* token) {

	// Get a pointer to the place in the buffer. We subtract
	// one because the index is already incremented.
	const char* buffer = lex->buffer + lex->idx - 1;

	// Loop through the keywords.
	for (uint32_t i = 0; i < sizeof(keywords) / sizeof(char*); ++i) {

		// If a keyword matches, set it, increment, and return.
		if (!strncmp(buffer, keywords[i], keyword_lens[i])) {

			// We just need to add the starting
			// index of keyword token types.
			token->type = BC_LEX_KEY_AUTO + i;

			// We need to minus one because the
			// index has already been incremented.
			lex->idx += keyword_lens[i] - 1;

			return BC_LEX_STATUS_SUCCESS;
		}
	}

	// We have a letter, so get the
	// character and set the type.
	token->data.character = buffer[0];
	token->type = BC_LEX_LETTER;

	return BC_LEX_STATUS_SUCCESS;
}
