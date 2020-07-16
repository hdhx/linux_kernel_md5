#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/uaccess.h>
#include <crypto/hash.h>
/*
#include <crypto/internal/hash.h>
*/
const char *raw = "testskrskr";

static int __init md5_init(void)
{
	char out[16];
	struct crypto_shash *md5;
	struct shash_desc *shash;

	md5 = crypto_alloc_shash("md5", 0, 0);
	if (IS_ERR(md5)) {
		pr_err("%s: crypto_alloc_shash failed!\n", __func__);
		return -1;
	}

	shash = kmalloc(sizeof(struct shash_desc) + crypto_shash_descsize(md5),
			GFP_KERNEL);
	if (!shash) {
		pr_err("%s: kmalloc failed!\n", __func__);
		return -ENOMEM;
	}

	shash->tfm = md5;
	shash->flags = 0;

	pr_info("Calculate MD5...\n");

	if (crypto_shash_init(shash)) {
		pr_err("%s: crypto_shash_init failed!\n", __func__);
		return -1;
	}

	if (crypto_shash_update(shash, raw, strlen(raw))) {
		pr_err("%s: crypto_shash_update failed!\n", __func__);
		return -1;
	}

	if (crypto_shash_final(shash, out)) {
		pr_err("%s: crypto_shash_final failed!\n", __func__);
		return -1;
	}

	kfree(shash);
	crypto_free_shash(md5);

	pr_info("%s MD5: %2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x\n", raw,
			(unsigned char)out[0], (unsigned char)out[1],
			(unsigned char)out[2], (unsigned char)out[3],
			(unsigned char)out[4], (unsigned char)out[5],
			(unsigned char)out[6], (unsigned char)out[7],
			(unsigned char)out[8], (unsigned char)out[9],
			(unsigned char)out[10], (unsigned char)out[11],
			(unsigned char)out[12], (unsigned char)out[13],
			(unsigned char)out[14], (unsigned char)out[15]);

	return 0;
}

static void __exit md5_exit(void)
{
	pr_info("%s\n", __func__);
}



MODULE_LICENSE("GPL");
module_init(md5_init);
module_exit(md5_exit);
