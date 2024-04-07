APPLE_TOOLS_VERSION := 0.0.3

APPLE_TOOLS_PATH = apple-tools
APPLE_TOOLS_DOWNLOAD_FILE = apple-tools.zip
APPLE_TOOLS_DOWNLOAD_URL = https://github.com/benjamink/fujinet-apple-tools/releases/download/$(APPLE_TOOLS_VERSION)/$(APPLE_TOOLS_DOWNLOAD_FILE)

get_apple_tools:
	@if [ ! -f "$(APPLE_TOOLS_PATH)/cur-version-$(APPLE_TOOLS_VERSION)" ]; then \
		if [ "$$(curl -Is $(APPLE_TOOLS_DOWNLOAD_URL) | head -n 1 | awk '{print $$2}')" == "404" ]; then \
			echo "ERROR: Unable to find file $(APPLE_TOOLS_DOWNLOAD_URL)"; \
			exit 1; \
		fi; \
		echo "Downloading apple-tools version $(APPLE_TOOLS_VERSION) from $(APPLE_TOOLS_DOWNLOAD_URL)"; \
		curl -sL $(APPLE_TOOLS_DOWNLOAD_URL) -o $(APPLE_TOOLS_DOWNLOAD_FILE); \
		echo "Unzipping to $(APPLE_TOOLS_PATH)"; \
		unzip -o $(APPLE_TOOLS_DOWNLOAD_FILE); \
		touch $(APPLE_TOOLS_PATH)/cur-version-$(APPLE_TOOLS_VERSION); \
		rm $(APPLE_TOOLS_DOWNLOAD_FILE); \
		echo "Unzip complete."; \
	else \
		echo "Current version $(APPLE_TOOLS_VERSION) already installed, skipping."; \
	fi