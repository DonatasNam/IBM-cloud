include $(TOPDIR)/rules.mk

PKG_NAME:=IBMcloud
PKG_VERSION:=1.0.0
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/IBMcloud
	DEPENDS:=+libubus +libubox +libblobmsg-json +libibm-c
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=Example program that interacts with ubus process
endef

define Package/IBMcloud/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/etc/config
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/IBMcloud $(1)/usr/bin
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/ibm_conf.yaml $(1)/etc/config
endef

$(eval $(call BuildPackage,IBMcloud))