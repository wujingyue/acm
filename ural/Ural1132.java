import java.io.*;
import java.util.*;
import java.math.*;

public class Ural1132 {

	static int modPow(int a, int b, int n) {
		int[] bin = new int[32];
		int tail = 0;
		while (b > 0) {
			bin[tail] = b % 2;
			b /= 2;
			tail++;
		}
		int ans = 1;
		for (int i = tail - 1; i >= 0; i--) {
			ans = ans * ans % n;
			if (bin[i] == 1)
				ans = ans * a % n;
		}
		return ans;
	}

	static int legendre(int a, int n) {
		if (a % n == 0)
			return 0;
		else {
			int b = modPow(a, (n - 1) / 2, n);
			if (b == 1)
				return 1;
			else {
				assert(b == n - 1);
				return -1;
			}
		}
	}

	static void solve(int a, int n) {
		if (n == 2) {
			assert(a == 1);
			System.out.println(1);
			return;
		}
		if (legendre(a, n) != 1) {
			System.out.println("No root");
			return;
		}
		int a1 = BigInteger.valueOf(a).modInverse(BigInteger.valueOf(n)).intValue();
		int q = n - 1, s = 0;
		while (q % 2 == 0) {
			q /= 2;
			s++;
		}
		Random r = new Random();
		int w;
		do {
			w = r.nextInt(n);
		} while (legendre(w, n) != -1);
		int v = modPow(w, q, n);
		int x = modPow(a, (q + 1) / 2, n);
		while (true) {
			int res = x * x % n * a1 % n, i = 0;
			while (res != 1) {
				res = res * res % n;
				i++;
			}
			if (i == 0)
				break;
			int b = v;
			for (int j = 0; j < s - i - 1; ++j)
				b = b * b % n;
			x = x * b % n;
		}
		int x1 = (n - x) % n;
		System.out.println(Math.min(x, x1) + " " + Math.max(x, x1));
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		for (int i = 0; i < t; i++) {
			int a = cin.nextInt(), n = cin.nextInt();
			solve(a, n);
		}
	}
}

