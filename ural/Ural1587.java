import java.io.*;
import java.util.*;
import java.math.*;

public class Ural1587 {

	static int[] a = new int[65536];

	static BigInteger update(BigInteger a, BigInteger b) {
		if (a == null)
			return b;
		else
			return a.max(b);
	}

	static BigInteger product(int i, int j) {
		BigInteger res = BigInteger.ONE;
		for (int k = i; k <= j; k++) {
			if (a[k] < 0)
				res = BigInteger.ZERO.subtract(res);
		}
		int n2 = 0, n3 = 0;
		for (int k = i; k <= j; k++) {
			if (Math.abs(a[k]) == 2)
				n2++;
			else if (Math.abs(a[k]) == 3)
				n3++;
		}
		res = res.multiply(BigInteger.valueOf(2).pow(n2));
		res = res.multiply(BigInteger.valueOf(3).pow(n3));
		return res;
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt();
		for (int i = 0; i < n; i++)
			a[i] = cin.nextInt();
		boolean has_zero = false;
		for (int i = 0; i < n; i++) {
			if (a[i] == 0) {
				has_zero = true;
				break;
			}
		}
		BigInteger ans;
		if (has_zero)
			ans = BigInteger.ZERO;
		else
			ans = null;
		int i = 0;
		while (i < n && a[i] == 0)
			i++;
		while (i < n) {
			int j = i + 1;
			while (j < n && a[j] != 0)
				j++;
			int num_negative = 0;
			for (int k = i; k < j; k++) {
				if (a[k] < 0)
					num_negative++;
			}
			if (num_negative % 2 == 0)
				ans = update(ans, product(i, j - 1));
			else if (i == j - 1)
				ans = update(ans, product(i, j - 1));
			else {
				int i1 = i;
				while (a[i1] > 0)
					i1++;
				int j1 = j - 1;
				while (a[j1] > 0)
					j1--;
				if (i <= j1 - 1)
					ans = update(ans, product(i, j1 - 1));
				if (i1 + 1 <= j - 1)
					ans = update(ans, product(i1 + 1, j - 1));
			}
			i = j + 1;
		}
		System.out.println(ans);
	}
}
