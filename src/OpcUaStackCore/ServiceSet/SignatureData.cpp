/*
   Copyright 2015-2018 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#include "OpcUaStackCore/ServiceSet/SignatureData.h"

namespace OpcUaStackCore
{

	SignatureData::SignatureData(void)
	: signature_()
	, algorithm_()
	{
	}

	SignatureData::~SignatureData(void)
	{
	}

	OpcUaStatusCode
	SignatureData::createSignature(
		MemoryBuffer& certificate,
		MemoryBuffer& nonce,
		PrivateKey& privateKey,
		CryptoBase& cryptoBase
	)
	{
		OpcUaStatusCode statusCode;

		// create plain text
		MemoryBuffer plainText(certificate.memLen() + nonce.memLen());
		memcpy(
			plainText.memBuf(),
			certificate.memBuf(),
			certificate.memLen()
		);
		memcpy(
			plainText.memBuf() + certificate.memLen(),
			nonce.memBuf(),
			nonce.memLen()
		);

		// get asymmetric key length
		uint32_t asymmetricKeyLen = 0;
		statusCode = cryptoBase.asymmetricKeyLen(privateKey, &asymmetricKeyLen);
		if (statusCode != Success) {
			return statusCode;
		}
		asymmetricKeyLen /= 8;

		MemoryBuffer signText;
		signText.resize(asymmetricKeyLen);

		// create signature
		uint32_t keyLen = asymmetricKeyLen;
		statusCode = cryptoBase.asymmetricSign(
			plainText.memBuf(),
			plainText.memLen(),
			privateKey,
			signText.memBuf(),
			&keyLen
		);
		if (statusCode != Success) {
			return statusCode;
		}

		signature(
			(OpcUaByte*)signText.memBuf(),
			signText.memLen()
		);
		algorithm(
			SignatureAlgs::signatureAlgToUri(cryptoBase.asymmetricSignatureAlgorithmId())
		);

		return statusCode;
	}

	OpcUaStatusCode
	SignatureData::verifySignature(
		MemoryBuffer& certificate,
		MemoryBuffer& nonce,
		PublicKey& publicKey,
		CryptoBase& cryptoBase
	)
	{
		OpcUaStatusCode statusCode;

		// check signature alg
		if (algorithm() != SignatureAlgs::signatureAlgToUri(cryptoBase.asymmetricSignatureAlgorithmId())) {
			return BadSecurityChecksFailed;
		}

		// get asymmetric key length
		uint32_t asymmetricKeyLen = 0;
		statusCode = cryptoBase.asymmetricKeyLen(publicKey, &asymmetricKeyLen);
		if (statusCode != Success) {
			return statusCode;
		}
		asymmetricKeyLen /= 8;

		// create plain text
		MemoryBuffer plainText(certificate.memLen() + nonce.memLen());
		memcpy(
			plainText.memBuf(),
			certificate.memBuf(),
			certificate.memLen()
		);
		memcpy(
			plainText.memBuf() + certificate.memLen(),
			nonce.memBuf(),
			nonce.memLen()
		);

		// create sign text
		MemoryBuffer signText(signature());

		// check signature length
		if (asymmetricKeyLen != signText.memLen()) {
			return BadSecurityChecksFailed;
		}

		// verify signature
		statusCode = cryptoBase.asymmetricVerify(
			plainText.memBuf(),
			plainText.memLen(),
			publicKey,
			signText.memBuf(),
			signText.memLen()
		);

		return statusCode;
	}

	void 
	SignatureData::signature(const OpcUaByte* buf, OpcUaInt32 bufLen)
	{
		signature_.value(buf, bufLen);
	}

	void 
	SignatureData::signature(OpcUaByte** buf, OpcUaInt32* bufLen) const
	{
		signature_.value(buf, bufLen);
	}

	OpcUaByteString
	SignatureData::signature(void)
	{
		return signature_;
	}

	void 
	SignatureData::algorithm(const std::string& algorithm)
	{
		algorithm_ = algorithm;
	}

	std::string 
	SignatureData::algorithm(void) const
	{
		return algorithm_.value();
	}

	void 
	SignatureData::opcUaBinaryEncode(std::ostream& os) const
	{
		algorithm_.opcUaBinaryEncode(os);
		signature_.opcUaBinaryEncode(os);
	}

	void 
	SignatureData::opcUaBinaryDecode(std::istream& is)
	{
		algorithm_.opcUaBinaryDecode(is);
		signature_.opcUaBinaryDecode(is);
	}

}
