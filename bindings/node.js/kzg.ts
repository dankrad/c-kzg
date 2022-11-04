// @ts-expect-error
import bindings from "bindings";

/**
 * The public interface of this module exposes the functions as specified by
 * https://github.com/ethereum/consensus-specs/blob/dev/specs/eip4844/polynomial-commitments.md#kzg
 */

export type BLSFieldElement = Uint8Array; // 32 bytes
export type KZGProof = Uint8Array; // 48 bytes
export type KZGCommitment = Uint8Array; // 48 bytes
export type Blob = Uint8Array; // 4096 * 32 bytes

type SetupHandle = Object;

// The C++ native addon interface
type KZG = {
  FIELD_ELEMENTS_PER_BLOB: number;
  BYTES_PER_FIELD: number;

  loadTrustedSetup: (filePath: string) => SetupHandle;

  freeTrustedSetup: (setupHandle: SetupHandle) => void;

  blobToKzgCommitment: (blob: Blob, setupHandle: SetupHandle) => KZGCommitment;

  computeAggregateKzgProof: (
    blobs: Blob[],
    setupHandle: SetupHandle
  ) => KZGProof;

  verifyAggregateKzgProof: (
    blobs: Blob[],
    expectedKzgCommitments: KZGCommitment[],
    kzgAggregatedProof: KZGProof,
    setupHandle: SetupHandle
  ) => boolean;

  // Currently unused -- not exported
  verifyKzgProof: (
    polynomialKzg: KZGCommitment,
    z: BLSFieldElement,
    y: BLSFieldElement,
    kzgProof: KZGProof,
    setupHandle: SetupHandle
  ) => boolean;
};

const kzg: KZG = bindings("kzg.node");

export const FIELD_ELEMENTS_PER_BLOB = kzg.FIELD_ELEMENTS_PER_BLOB;
export const BYTES_PER_FIELD = kzg.BYTES_PER_FIELD;

// Stored as internal state
let setupHandle: SetupHandle | undefined;

export function loadTrustedSetup(filePath: string): void {
  if (setupHandle) {
    throw new Error(
      "Call freeTrustedSetup before loading a new trusted setup."
    );
  }
  setupHandle = kzg.loadTrustedSetup(filePath);
}

export function freeTrustedSetup(): void {
  if (!setupHandle) {
    throw new Error("You must call loadTrustedSetup before freeTrustedSetup.");
  }
  kzg.freeTrustedSetup(setupHandle);
  setupHandle = undefined;
}

export function blobToKzgCommitment(blob: Blob): KZGCommitment {
  if (!setupHandle) {
    throw new Error("You must call loadTrustedSetup to initialize KZG.");
  }
  return kzg.blobToKzgCommitment(blob, setupHandle);
}

export function computeAggregateKzgProof(blobs: Blob[]): KZGProof {
  if (!setupHandle) {
    throw new Error("You must call loadTrustedSetup to initialize KZG.");
  }
  return kzg.computeAggregateKzgProof(blobs, setupHandle);
}

export function verifyAggregateKzgProof(
  blobs: Blob[],
  expectedKzgCommitments: KZGCommitment[],
  kzgAggregatedProof: KZGProof
): boolean {
  if (!setupHandle) {
    throw new Error("You must call loadTrustedSetup to initialize KZG.");
  }
  return kzg.verifyAggregateKzgProof(
    blobs,
    expectedKzgCommitments,
    kzgAggregatedProof,
    setupHandle
  );
}