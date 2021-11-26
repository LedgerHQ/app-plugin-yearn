import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx } from './test.fixture';
import { ethers } from "ethers";

const contractAddr = "0xA696a63cc78DfFa1a63E9E50587C197387FF6C7E";
const recipient = "0xB8c93dF4E1e6b1097889554D9294Dfb42814063a"; //Never use this address for anything other than tests - compromised
const AMOUNT_TO_DEPOSIT = '212345678'; // 2.12345678
const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Deposit Tokens with Recipient 8 decimals', zemu("nanos", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function deposit(uint256, address)']);
  const {data} = await contract.populateTransaction.deposit(AMOUNT_TO_DEPOSIT, recipient);
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_deposit_recipient_8', [BASE_SCREENS_S + 3, 0]);
  await tx;
}));

test('[Nano X] Deposit Tokens with Recipient 8 decimals', zemu("nanox", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function deposit(uint256, address)']);
  const {data} = await contract.populateTransaction.deposit(AMOUNT_TO_DEPOSIT, recipient);

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_deposit_recipient_8', [BASE_SCREENS_X + 1, 0]);
  await tx;
}));
