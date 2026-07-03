# misc
A oddball collection of tools...

The tools included are:

        ip4innet        A tool to verify if in IPv4 address is in a given
                        subnet. It takes two or three arguments:

                        - IP Address (mandatory)
                        - Subnet (mandatory)
                        - Netmask (optional)

                        The Subnet can be expressed as a CIDR subnet, e.g.
                        Subnet/mask. When expressed in this form, the Netmask
                        argument should not be provided. Conversely, when a
                        Netmask is specified, the Subnet should not be in CIDR
                        format.

                        The tool returns the string 'TRUE' if the IP Address is
                        in the Subnet, and FALSE otherwise. The command exits 0
                        when TRUE, and 1 when FALSE (or if there is an error)

To build and install these tools, run the following commands:

        % make
        % sudo make install

Please address all bug reports to John Howie (john@howieconsultinginc.com).

John
