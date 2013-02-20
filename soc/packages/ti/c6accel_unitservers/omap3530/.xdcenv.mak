#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /usr/local/dvsdk/c6accel_1_01_00_06/soc;packages;/usr/local/dvsdk/xdais_6_26_01_03/packages;/usr/local/dvsdk/framework-components_2_26_00_01/packages;/usr/local/dvsdk/framework-components_2_26_00_01/fctools/packages;/usr/local/dvsdk/dspbios_5_41_03_17/packages;/usr/local/dvsdk/biosutils_1_02_02/packages;/usr/local/dvsdk/linuxutils_2_26_01_02/packages;/usr/local/dvsdk/dsplink_1_65_00_02/packages;/usr/local/dvsdk/dsplink_1_65_00_02;/usr/local/dvsdk/codec_engine_2_26_02_11/packages;/usr/local/dvsdk/codec_engine_2_26_02_11/cetools/packages;/usr/local/dvsdk/edma3lld_01_11_00_03/packages;/packages
override XDCROOT = /usr/local/dvsdk/xdctools_3_16_03_36
override XDCBUILDCFG = /usr/local/dvsdk/c6accel_1_01_00_06/config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = "prod"
override XDCTARGETS = ti.targets.C64P
endif
#
ifeq (0,1)
PKGPATH = /usr/local/dvsdk/c6accel_1_01_00_06/soc;packages;/usr/local/dvsdk/xdais_6_26_01_03/packages;/usr/local/dvsdk/framework-components_2_26_00_01/packages;/usr/local/dvsdk/framework-components_2_26_00_01/fctools/packages;/usr/local/dvsdk/dspbios_5_41_03_17/packages;/usr/local/dvsdk/biosutils_1_02_02/packages;/usr/local/dvsdk/linuxutils_2_26_01_02/packages;/usr/local/dvsdk/dsplink_1_65_00_02/packages;/usr/local/dvsdk/dsplink_1_65_00_02;/usr/local/dvsdk/codec_engine_2_26_02_11/packages;/usr/local/dvsdk/codec_engine_2_26_02_11/cetools/packages;/usr/local/dvsdk/edma3lld_01_11_00_03/packages;/packages;/usr/local/dvsdk/xdctools_3_16_03_36/packages;../../..
HOSTOS = Linux
endif
