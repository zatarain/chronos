FROM zatarain/cpp:development
ENV LD_LIBRARY_PATH=/usr/local/lib \
	TERM=xterm \
	PATH=${PATH}:/build/bin
RUN echo "${TERM}" && tabs -4
WORKDIR /root
RUN git clone https://github.com/zatarain/utz.git
COPY . .
WORKDIR /root/utz
RUN make install && rm -rf aut
WORKDIR /root
#RUN make out/chronos && make install
#RUN utz test
CMD ["bash"]