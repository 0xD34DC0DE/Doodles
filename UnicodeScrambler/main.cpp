#include <random>
#include <iostream>
#include <sstream>
#include <windows.h>


std::wstring randomDiacritical(unsigned int charCount)
{
	// returns diacritical array in the form of a wstring
	static std::random_device rd;
	static std::mt19937 mt(rd());
	static std::uniform_int_distribution<> rnd(0, 125);

	std::wstring str(charCount, L'\0'); // Allocate string of specified size

	for (unsigned int i = 0; i < charCount; i++)
	{
		unsigned int randNum = rnd(mt);

		if (0 <= randNum && randNum <= 111) // Combining Diacritical Marks (0300-036F)
		{
			str[i] = static_cast<wchar_t>(randNum + 768);
		}
		else if (112 <= randNum && randNum <= 121) // Combining Diacritical Marks Supplement (1DC0-1DCA)
		{
			str[i] = static_cast<wchar_t>(randNum - 111 + 7616);
		}
		else if (122 <= randNum && randNum <= 125) // Combining Half Marks (FE20-FE23)
		{
			str[i] = static_cast<wchar_t>(randNum - 121 + 65056);
		}
	}

	return str;
}

std::wstring getClipboardText(HWND hwnd)
{
	try {
		// Try opening the clipboard
		if (!OpenClipboard(hwnd))
			throw std::exception("Unable to open clipboard");

		// Get handle of clipboard object for UTF-16 text
		HANDLE hData = GetClipboardData(CF_UNICODETEXT);
		if (hData == nullptr)
			throw std::exception("Unable to get handle of clipboard");

		// Lock the handle to get the actual text pointer
		wchar_t * pszText = static_cast<wchar_t*>(GlobalLock(hData));
		if (pszText == nullptr)
			throw std::exception("Unable to obtain lock on text pointer");

		// Save text in a string class instance
		std::wstring text(pszText);

		// Release the lock
		GlobalUnlock(hData);

		// Release the clipboard
		CloseClipboard();

		return text;
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		return std::wstring();
	}
	catch (...)
	{
		std::cerr << "Non-stantard exeption raised\n";
		return std::wstring();
	}
}

void setClipboardText(const std::wstring& text, HWND hwnd)
{
	try {
		// Try opening the clipboard
		if (!OpenClipboard(hwnd))
			throw std::exception("Unable to open clipboard");

		EmptyClipboard();

		HGLOBAL hBuffer = GlobalAlloc(GMEM_DDESHARE, (text.size() + 1) * sizeof(wchar_t));
		if (hBuffer == nullptr)
			throw std::exception("Unable to allocate memory for handle buffer");

		wchar_t* buffer = (wchar_t*)GlobalLock(hBuffer);
		if (buffer == nullptr)
			throw std::exception("Unable to obtain global lock on buffer");

		wcscpy_s(buffer, text.size() + 1, text.c_str());
		GlobalUnlock(hBuffer);
		SetClipboardData(CF_UNICODETEXT, hBuffer);
		CloseClipboard();
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
	}
	catch (...)
	{
		std::cerr << "Non-stantard exeption raised\n";
	}
}

void zalgoClipboard(unsigned int charCount)
{
	std::wstring clipboardString = getClipboardText(nullptr);

	std::wstring zStr;

	for (auto& c : clipboardString)
		zStr += c + randomDiacritical(charCount);

	setClipboardText(zStr, nullptr);
}

int main(unsigned int argc, char** argv)
{
	int diacCount = 1;
	if (argc == 2)
	{
		try {
			diacCount = std::atoi(argv[1]);
			if (diacCount == 0)
				throw std::exception("Argument is invalid");
			if (diacCount < 0)
				throw std::exception("Argument is negative");
		}
		catch (const std::exception &exc)
		{
			std::printf("ERROR: %s\n", exc.what());
		}
	}

	zalgoClipboard(diacCount);

	return 0;
}