#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int ft_ret;
	int std_ret;
	int test_var = 42;
	void *ptr = &test_var;
	void *null_ptr = NULL;
	char *null_str = NULL;
	const char *fmt;

	printf("===================================================\n");
	printf("   TESTING %%c AND %%s WITH WIDTH AND '-' FLAG   \n");
	printf("===================================================\n\n");

	// --- CHAR (%c) TESTS ---
	printf("--- [CHAR] Test 1: Width Only (Right-Aligned) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%5c|\n", 'A');
	std_ret =    printf("printf     : |%5c|\n", 'A');
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [CHAR] Test 2: Left-Aligned ('-' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-5c|\n", 'Z');
	std_ret =    printf("printf     : |%-5c|\n", 'Z');
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [CHAR] Test 3: Null Character '\\0' with Width ---\n");
	ft_ret  = ft_printf("ft_printf  : |%5c|\n", '\0');
	std_ret =    printf("printf     : |%5c|\n", '\0');
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [CHAR] Test 4: Null Character '\\0' Left-Aligned ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-5c|\n", '\0');
	std_ret =    printf("printf     : |%-5c|\n", '\0');
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- STRING (%s) TESTS ---
	printf("--- [STRING] Test 5: Width Only (Right-Aligned) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%10s|\n", "hello");
	std_ret =    printf("printf     : |%10s|\n", "hello");
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [STRING] Test 6: Left-Aligned ('-' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-10s|\n", "hello");
	std_ret =    printf("printf     : |%-10s|\n", "hello");
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [STRING] Test 7: String Length > Width ---\n");
	ft_ret  = ft_printf("ft_printf  : |%3s|\n", "42Network");
	std_ret =    printf("printf     : |%3s|\n", "42Network");
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- POINTER (%p) TESTS ---
	printf("--- [POINTER] Test 8: Valid Pointer + Width ---\n");
	ft_ret  = ft_printf("ft_printf  : |%20p|\n", ptr);
	std_ret =    printf("printf     : |%20p|\n", ptr);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [POINTER] Test : Valid Pointer + Left-Aligned ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-20p|\n", ptr);
	std_ret =    printf("printf     : |%-20p|\n", ptr);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [POINTER] Test 7: NULL Pointer + Width ---\n");
	ft_ret  = ft_printf("ft_printf  : |%15p|\n", null_ptr);
	std_ret =    printf("printf     : |%15p|\n", null_ptr);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [POINTER] Test 8: NULL Pointer + Left-Aligned ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-15p|\n", null_ptr);
	std_ret =    printf("printf     : |%-15p|\n", null_ptr);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- HEX (%x || %X) TESTS ---
	// --- 1. BASIC & VALUE TESTS ---
	printf("--- [HEX] 1. Standard Values & Zero ---\n");
	ft_ret  = ft_printf("ft_printf  : |%x| |%X| |%x|\n", 255, 255, 0);
	std_ret =    printf("printf     : |%x| |%X| |%x|\n", 255, 255, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [HEX] 2. UINT_MAX & Negative (Cast to Unsigned) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%x| |%X|\n", UINT_MAX, -42);
	std_ret =    printf("printf     : |%x| |%X|\n", UINT_MAX, -42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 2. WIDTH AND ALIGNMENT (-) ---
	printf("--- [HEX] 3. Width Only (Right-Aligned) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%10x| |%10X|\n", 305419896, 305419896);
	std_ret =    printf("printf     : |%10x| |%10X|\n", 305419896, 305419896);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [HEX] 4. Left-Aligned ('-' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-10x| |%-10X|\n", 42, 42);
	std_ret =    printf("printf     : |%-10x| |%-10X|\n", 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 3. ZERO PADDING (0) ---
	printf("--- [HEX] 5. Zero-Padding ('0' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%010x| |%010X|\n", 255, 255);
	std_ret =    printf("printf     : |%010x| |%010X|\n", 255, 255);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 4. HASH FLAG (#) ---
	printf("--- [HEX] 6. Hash Flag ('#' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%#x| |%#X|\n", 42, 42);
	std_ret =    printf("printf     : |%#x| |%#X|\n", 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [HEX] 7. Hash Flag with Zero Value (Should NOT print 0x) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%#x| |%#X|\n", 0, 0);
	std_ret =    printf("printf     : |%#x| |%#X|\n", 0, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 5. PRECISION (.) ---
	printf("--- [HEX] 8. Precision Only ---\n");
	ft_ret  = ft_printf("ft_printf  : |%.5x| |%.5X|\n", 42, 42);
	std_ret =    printf("printf     : |%.5x| |%.5X|\n", 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [HEX] 9. Precision .0 with Zero Value (Prints Nothing) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%.0x| |%.0X|\n", 0, 0);
	std_ret =    printf("printf     : |%.0x| |%.0X|\n", 0, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 6. CRITICAL COMBINATIONS & EDGE CASES ---
	printf("--- [HEX] 10. Hash + Zero-Padding ('#010x') ---\n");
	ft_ret  = ft_printf("ft_printf  : |%#010x| |%#010X|\n", 42, 42);
	std_ret =    printf("printf     : |%#010x| |%#010X|\n", 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [HEX] 11. Hash + Left-Align ('-#10x') ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-#10x| |%-#10X|\n", 42, 42);
	std_ret =    printf("printf     : |%-#10x| |%-#10X|\n", 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [HEX] 12. Width + Precision + Zero-Flag (Precision overrides '0') ---\n");
	ft_ret  = ft_printf("ft_printf  : |%010.5x| |%010.5X|\n", 42, 42);
	fmt = "printf     : |%010.5x| |%010.5X|\n";
	std_ret =    printf(fmt, 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [HEX] 13. Hash + Precision .0 + Value 0 + Width ---\n");
	ft_ret  = ft_printf("ft_printf  : |%#5.0x| |%#-5.0X|\n", 0, 0);
	std_ret =    printf("printf     : |%#5.0x| |%#-5.0X|\n", 0, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- CHAR (%c) TESTS ---
	// --- 1. BASIC & VALUE RANGE TESTS ---
	printf("--- [UNSIGNED] 1. Standard Values & Boundaries ---\n");
	ft_ret  = ft_printf("ft_printf  : |%u| |%u| |%u|\n", 0, 42, UINT_MAX);
	std_ret =    printf("printf     : |%u| |%u| |%u|\n", 0, 42, UINT_MAX);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [UNSIGNED] 2. Negative Value Input (Implicit Unsigned Cast) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%u| |%u|\n", -1, -42);
	std_ret =    printf("printf     : |%u| |%u|\n", -1, -42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 2. WIDTH AND ALIGNMENT (-) ---
	printf("--- [UNSIGNED] 3. Width Only (Right-Aligned) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%10u| |%3u|\n", 12345, 12345);
	std_ret =    printf("printf     : |%10u| |%3u|\n", 12345, 12345);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [UNSIGNED] 4. Left-Aligned ('-' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-10u| |%-3u|\n", 12345, 12345);
	std_ret =    printf("printf     : |%-10u| |%-3u|\n", 12345, 12345);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 3. ZERO PADDING (0) ---
	printf("--- [UNSIGNED] 5. Zero-Padding ('0' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%010u| |%03u|\n", 42, 12345);
	std_ret =    printf("printf     : |%010u| |%03u|\n", 42, 12345);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 4. PRECISION (.) ---
	printf("--- [UNSIGNED] 6. Precision Only ---\n");
	ft_ret  = ft_printf("ft_printf  : |%.5u| |%.2u|\n", 42, 12345);
	std_ret =    printf("printf     : |%.5u| |%.2u|\n", 42, 12345);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [UNSIGNED] 7. Precision .0 with Zero Value (Prints Nothing) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%.0u| |%.u|\n", 0, 0);
	std_ret =    printf("printf     : |%.0u| |%.u|\n", 0, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 5. COMBINATIONS & OVERRIDES ---
	printf("--- [UNSIGNED] 8. Precision + Width ---\n");
	ft_ret  = ft_printf("ft_printf  : |%10.5u| |%5.10u|\n", 42, 42);
	std_ret =    printf("printf     : |%10.5u| |%5.10u|\n", 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [UNSIGNED] 9. Precision + Width + Left-Align ('-') ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-10.5u|\n", 42);
	std_ret =    printf("printf     : |%-10.5u|\n", 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [UNSIGNED] 10. Precision Overrides Zero-Flag ('0' + '.') ---\n");
	ft_ret  = ft_printf("ft_printf  : |%010.5u|\n", 42);
	fmt = "printf     : |%010.5u|\n";
	std_ret =    printf(fmt, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [UNSIGNED] 11. Left-Align Overrides Zero-Flag ('-' + '0') ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-010u|\n", 42);
	fmt = "printf     : |%-010u|\n";
	std_ret = printf(fmt, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [UNSIGNED] 12. Width + Precision .0 + Value 0 ---\n");
	ft_ret  = ft_printf("ft_printf  : |%10.0u| |%-10.0u|\n", 0, 0);
	std_ret =    printf("printf     : |%10.0u| |%-10.0u|\n", 0, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- INT (%i || %d ) TESTS ---
	// --- 1. BASIC & VALUE RANGE TESTS ---
	printf("--- [SIGNED] 1. Standard Values & Boundaries ---\n");
	ft_ret  = ft_printf("ft_printf  : |%d| |%i| |%d| |%i|\n", 0, -42, INT_MAX, INT_MIN);
	std_ret =    printf("printf     : |%d| |%i| |%d| |%i|\n", 0, -42, INT_MAX, INT_MIN);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 2. SIGN FLAGS (+ and Space) ---
	printf("--- [SIGNED] 2. Plus Flag ('+') ---\n");
	ft_ret  = ft_printf("ft_printf  : |%+d| |%+d| |%+d|\n", 42, -42, 0);
	std_ret =    printf("printf     : |%+d| |%+d| |%+d|\n", 42, -42, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 3. Space Flag (' ') ---\n");
	ft_ret  = ft_printf("ft_printf  : |% d| |% d| |% d|\n", 42, -42, 0);
	std_ret =    printf("printf     : |% d| |% d| |% d|\n", 42, -42, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 4. Plus Overrides Space Flag ('+' + ' ') ---\n");
	fmt = "printf     : |% +d| |%+ d|\n";
	ft_ret  = ft_printf("ft_printf  : |% +d| |%+ d|\n", 42, 42);
	std_ret =    printf(fmt, 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 3. WIDTH AND ALIGNMENT (-) ---
	printf("--- [SIGNED] 5. Width Only (Right-Aligned) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%10d| |%10i|\n", 123, -123);
	std_ret =    printf("printf     : |%10d| |%10i|\n", 123, -123);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 6. Left-Aligned ('-' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-10d| |%-10i|\n", 123, -123);
	std_ret =    printf("printf     : |%-10d| |%-10i|\n", 123, -123);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 4. ZERO PADDING (0) ---
	printf("--- [SIGNED] 7. Zero-Padding ('0' Flag) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%010d| |%010i|\n", 42, -42);
	std_ret =    printf("printf     : |%010d| |%010i|\n", 42, -42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 8. Zero-Padding + Plus/Space Flag ---\n");
	ft_ret  = ft_printf("ft_printf  : |%0+10d| |%0 10d|\n", 42, 42);
	std_ret =    printf("printf     : |%0+10d| |%0 10d|\n", 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 5. PRECISION (.) ---
	printf("--- [SIGNED] 9. Precision Only ---\n");
	ft_ret  = ft_printf("ft_printf  : |%.5d| |%.5i|\n", 42, -42);
	std_ret =    printf("printf     : |%.5d| |%.5i|\n", 42, -42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 10. Precision .0 with Zero Value (Prints Nothing) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%.0d| |%.i|\n", 0, 0);
	std_ret =    printf("printf     : |%.0d| |%.i|\n", 0, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- 6. COMBINATIONS & OVERRIDES ---
	printf("--- [SIGNED] 11. Precision + Width + Sign Flags ---\n");
	ft_ret  = ft_printf("ft_printf  : |%10.5d| |%+10.5d| |% 10.5d|\n", -42, 42, 42);
	std_ret =    printf("printf     : |%10.5d| |%+10.5d| |% 10.5d|\n", -42, 42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 12. Precision Overrides Zero-Flag ('0' + '.') ---\n");
	fmt = "printf     : |%010.5d| |%0+10.5d|\n";
	ft_ret  = ft_printf("ft_printf  : |%010.5d| |%0+10.5d|\n", -42, 42);
	std_ret =    printf(fmt, -42, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 13. Left-Align Overrides Zero-Flag ('-' + '0') ---\n");
	fmt = "printf     : |%-010d|\n";
	ft_ret  = ft_printf("ft_printf  : |%-010d|\n", 42);
	std_ret =    printf(fmt, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [SIGNED] 14. Width + Precision .0 + Value 0 + Plus Flag ---\n");
	ft_ret  = ft_printf("ft_printf  : |%+10.0d| |%---------------+10.0d|\n", 0, 0);
	fmt = "printf     : |%+10.0d| |%---------------+10.0d|\n";
	std_ret =    printf(fmt, 0, 0);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- MIXED / INTERLEAVED CONVERSIONS ---
	printf("--- [MIXED] 1. Multiple Different Conversions in One Call ---\n");
	ft_ret  = ft_printf("ft_printf  : |%c-%s-%d-%x-%p|\n", 'A', "hi", -42, 255, ptr);
	std_ret =    printf("printf     : |%c-%s-%d-%x-%p|\n", 'A', "hi", -42, 255, ptr);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [MIXED] 2. Literal Text Before, Between, and After Conversions ---\n");
	ft_ret  = ft_printf("ft_printf  : start %10d middle %-10s end %05x done\n", 42, "hi", 255);
	std_ret =    printf("printf     : start %10d middle %-10s end %05x done\n", 42, "hi", 255);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [MIXED] 3. Flags From One Conversion Must Not Leak Into Literal Text ---\n");
	ft_ret  = ft_printf("ft_printf  : [%10d] literal text after wide conversion\n", 5);
	std_ret =    printf("printf     : [%10d] literal text after wide conversion\n", 5);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [MIXED] 4. Flags Must Not Leak Between Two Conversions Either ---\n");
	ft_ret  = ft_printf("ft_printf  : [%10d][%d]\n", 5, 5);
	std_ret =    printf("printf     : [%10d][%d]\n", 5, 5);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [MIXED] 5. Consecutive Conversions With No Literal Between ---\n");
	ft_ret  = ft_printf("ft_printf  : |%d%d%d|\n", 1, 2, 3);
	std_ret =    printf("printf     : |%d%d%d|\n", 1, 2, 3);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [MIXED] 6. Percent Literal Mixed With Real Conversions ---\n");
	ft_ret  = ft_printf("ft_printf  : |100%% done, count=%d|\n", 5);
	std_ret =    printf("printf     : |100%% done, count=%d|\n", 5);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	// --- FULL FLAG COMBINATIONS ---
	printf("--- [COMBO] 1. Every Numeric Flag At Once (hash+zero+width+precision) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%#010.5x|\n", 42);
	fmt = "printf     : |%#010.5x|\n";
	std_ret =    printf(fmt, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [COMBO] 2. Every Signed Flag At Once (plus+zero+width+precision) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%+010.5d|\n", 42);
	fmt = "printf     : |%+010.5d|\n";
	std_ret =    printf(fmt, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [COMBO] 3. Left-Align + Zero + Precision Together (left-align wins) ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-010.5d|\n", 42);
	fmt = "printf     : |%-010.5d|\n";
	std_ret =    printf(fmt, 42);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [COMBO] 4. String Precision + Width + Left-Align Together ---\n");
	ft_ret  = ft_printf("ft_printf  : |%-10.3s|\n", "hello world");
	std_ret =    printf("printf     : |%-10.3s|\n", "hello world");
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [COMBO] 5. NULL String With Precision ---\n");
	ft_ret  = ft_printf("ft_printf  : |%.2s|\n", null_str);
	std_ret =    printf("printf     : |%.2s|\n", null_str);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	printf("--- [COMBO] 6. Large Width Value ---\n");
	ft_ret  = ft_printf("ft_printf  : |%50d|\n", 1);
	std_ret =    printf("printf     : |%50d|\n", 1);
	printf("Return Values -> ft: %d | std: %d\n\n", ft_ret, std_ret);

	return (0);
}
