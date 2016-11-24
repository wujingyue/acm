import java.io.*;
import java.util.*;
import java.math.*;

public class Ural1174 {

	final static int MAX_N = 128;

	static int[] a = new int[MAX_N];
	static BigInteger ans;
	static int n;

	static void input() {
		Scanner cin = new Scanner(System.in);
		n = cin.nextInt();
		for (int i = 0; i < n; i++) {
			a[i] = cin.nextInt();
			a[i]--;
		}
	}

	static BigInteger work(int[] a, int n) {
		if (n == 1)
			return BigInteger.ZERO;
		int pos = -1;
		for (int i = 0; i < n; i++) {
			if (a[i] == n - 1) {
				pos = i;
				break;
			}
		}
		assert(pos >= 0);
		for (int i = pos; i + 1 < n; i++)
			a[i] = a[i + 1];
		BigInteger res = work(a, n - 1);
		if (res.mod(BigInteger.valueOf(2)).equals(BigInteger.ZERO)) {
			res = res.multiply(BigInteger.valueOf(n));
			res = res.add(BigInteger.valueOf(n - 1 - pos));
		} else {
			res = res.multiply(BigInteger.valueOf(n));
			res = res.add(BigInteger.valueOf(pos));
		}
		return res;
	}

	static void solve() {
		ans = work(a, n);
	}
	
	static void output() {
		System.out.println(ans.add(BigInteger.ONE));
	}

	public static void main(String[] args) {
		input();
		solve();
		output();
	}
}
