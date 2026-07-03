/* File: ip4innet.c
**
** Author: (c) John Howie, Howie Consulting Inc., 2026.
**
** Description
**
**	This program takes arguments, the first of which is an IP address, and
** determines if it is in a subnet specified by the second argument. The second
** argument can be in CIDR format. If it is not (or if the subnet cannot be
** calculated from it), a third (optional) argument specifies the subnet mask.
**
** Modifications
**
** 2026-07-02	John Howie	Original.
**
*/

# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <sys/socket.h>
# include <arpa/inet.h>

extern int errno;

int main (int argc, char *argv []);

int main (int argc, char *argv [])
{
	in_addr_t       ip_address, ip_subnet, ip_netmask;
	struct in_addr  ip_net_subnet;
	int             netmaskbits;
	char            errormsg [256 +1];

	// Check we got two or three arguments, and return if we did not, as we
	// cannot proceed. Make sure that the first argument is not a NULL value

	if ((argc != 3) && (argc != 4)) {
		// We did not get the correct number of arguments. Display some
		// useful information, and then return

		printf ("Usage: %s <ip_address> <ip_subnet[/maskbits]> [ip_netmask]\n", argv [0]);
		return 1;
	}

	// Get the IP address value provided by the user, and turn it into a
	// number we can work with

	ip_address = ntohl (inet_addr (argv [1]));

	// Now, we need to calculate the subnet. This is easy if the user
	// provided a subnet mask (three arguments)

	if (argc == 4) {
		// The user supplied the netmask. This makes it extremely easy
		// as we just read the subnet and the netmask as-is. Note that
		// we use inet_addr () to read the netmask, as inet_network
		// does not accept 0x<mask> notation!

		ip_subnet = inet_network (argv [2]);
		ip_netmask = ntohl (inet_addr (argv [3]));
	}
	else {
		// We have a network / CIDR notation

		memset (&ip_net_subnet, 0, sizeof (struct in_addr));
		netmaskbits = inet_net_pton (AF_INET, argv [2], &ip_net_subnet, sizeof (struct in_addr));
		if (netmaskbits == -1) {
			// An error occurred. All we can do is return an error

			fprintf (stderr, "Unable to calculate network and mask for %s (inet_net_pton)\n", argv [2]);
			return 1;
		}
 
		// Copy over the subnet and calculate the netmask, based on the
		// number of bits in the network address

		ip_subnet = ntohl (ip_net_subnet.s_addr);
		ip_netmask = (0xFFFFFFFF << (32 - netmaskbits));
	}

	// Now that we have the IP Address, the Subnet, and the Netmask values,
	// we can check if the IP Adddress is in the Subnet

	if ((ip_address & ip_netmask) == (ip_subnet & ip_netmask)) {
		// The IP Address is in the Subnet

		printf ("TRUE\n");
		return 0;
	}
	else {
		// The IP Address is NOT in the Subnet

		printf ("FALSE\n");
		return 1;
	}
}
