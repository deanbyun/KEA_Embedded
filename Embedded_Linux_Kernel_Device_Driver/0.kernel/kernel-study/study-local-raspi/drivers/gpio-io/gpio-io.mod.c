#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xf6dfbf7c, "gpio_to_desc" },
	{ 0x5a5bab24, "gpiod_unexport" },
	{ 0xfe990052, "gpio_free" },
	{ 0x76646418, "device_destroy" },
	{ 0x70dd78f1, "class_destroy" },
	{ 0x34bebc18, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x8e1ca6d9, "cdev_init" },
	{ 0x89b05fd3, "cdev_add" },
	{ 0x58cffff9, "class_create" },
	{ 0xa76c78c8, "device_create" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xc0a32b3a, "gpiod_direction_output_raw" },
	{ 0xf208bdeb, "gpiod_export" },
	{ 0x8ec5d1e5, "gpiod_get_raw_value" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x5f754e5a, "memset" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0x558a7676, "gpiod_set_raw_value" },
	{ 0xa6f3f0f1, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "485423D6BEEB32A1AC4E887");
