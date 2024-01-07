# SPDX-FileCopyrightText: 2023 The unpaper authors
#
# SPDX-License-Identifier: MIT

import textwrap
from typing import IO

import click
from google.protobuf import text_format

import unpaper_pb2


def bin_to_c(message: bytes) -> str:
    return textwrap.dedent(
        f"""
            #include <stdint.h>

            static const uint8_t DEFAULT_JOB_PARAMETERS[] = {{
                {', '.join(hex(b) for b in message)}
            }};
        """)


@click.command()
@click.argument('job-parameters-textproto', type=click.File('r'))
@click.argument('output', type=click.File('w'))
def main(job_parameters_textproto: IO[str], output: IO[str]) -> None:
    text_proto = job_parameters_textproto.read()
    message = text_format.Parse(text_proto, unpaper_pb2.JobParameters())
    binary = message.SerializeToString()

    output.write(bin_to_c(binary))


if __name__ == '__main__':
    main()