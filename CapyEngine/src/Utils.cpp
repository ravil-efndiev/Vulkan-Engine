#include "Utils.h"

namespace cp {
	const char* debugSeverityPrefix(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
		switch (severity) {
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			return "\033[36m[Vulkan Verbose]\033[0m";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			return "\033[36m[Vulkan Info]\033[0m";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			return "\033[31m[Vulkan Error]\033[0m";
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			return "\033[33m[Vulkan Warning]\033[0m";
			break;
		default:
			return "";
		}
	}

	void enableVirtualTerminalProcessing() {
#ifdef WIN32
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE) {
			return;
		}
		DWORD dwMode = 0;
		if (!GetConsoleMode(hOut, &dwMode)) {
			return;
		}
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
#endif
	}

	std::vector<char> readFileBin(const std::filesystem::path& path) {
		std::ifstream file(path, std::ios::binary | std::ios::ate);

		if (!file.is_open()) {
			throw std::runtime_error("couldnt open file from path '" + path.string() + "'");
		}

		std::vector<char> bytes(file.tellg());
		file.seekg(0);
		file.read(bytes.data(), bytes.size());
		return bytes;
	}

	void checkVkResult(VkResult result, std::string_view errorMessage) {
		if (result != VK_SUCCESS) {
			throw std::runtime_error(errorMessage.data());
		}
	}

	void checkVkResult(const std::initializer_list<VkResult>& results, std::string_view errorMessage) {
		CP_ASSERT(results.size() > 0, "results list cannot be empty");
		for (VkResult result : results) {
			if (result != VK_SUCCESS) {
				throw std::runtime_error(errorMessage.data());
			}
		}
	}
}
